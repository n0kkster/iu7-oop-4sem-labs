namespace OOP_LAB_04;

public class Controller
{
    public enum ControllerState
    {
        Idle,
        GotTargetFromFloor,
        GotTargetFromCabin,
        PreparingToMove,
        Moving,
        Arrived
    }

    private int _currentFloor = 1;
    private ElevatorMoveDirection _direction = ElevatorMoveDirection.None;
    private int _target = NoTarget;
    private readonly RequestedDirection[] _floorStates;

    private ControllerState _state = ControllerState.Idle;

    private readonly Dictionary<ElevatorMoveDirection, RequestedDirection> _relationships = new()
    {
        [ElevatorMoveDirection.Up] = RequestedDirection.Up,
        [ElevatorMoveDirection.Down] = RequestedDirection.Down,
        [ElevatorMoveDirection.None] = RequestedDirection.None
    };

    private readonly Dictionary<ElevatorMoveDirection, string> _translations = new()
    {
        [ElevatorMoveDirection.Up] = "Вверх",
        [ElevatorMoveDirection.Down] = "Вниз",
        [ElevatorMoveDirection.None] = "Нет"
    };

    public const int FloorAmount = 10;
    public const int NoTarget = -1;

    public event Action<int, ElevatorMoveDirection>? ArrivedAtFloorDisplay;
    public event Action<int>? FloorPassedDisplay;

    public event EventHandler? TargetReached;
    public event EventHandler? TargetFound;

    public event EventHandler? CabinNextFloor;
    public event EventHandler? StartCabin;
    public event EventHandler? StopCabin;
    public event EventHandler? PrepareCabin;
    public event EventHandler? OpenCabin;
    
    public Controller()
    {
        _floorStates = new RequestedDirection[FloorAmount];

        TargetReached += OnTargetReached;
        TargetFound += OnTargetFound;
    }

    // =========== ОБРАБОТЧИКИ СОСТОЯНИЙ ===========

    // Обработчик состояния Moving
    public void MovingHandler(object? sender, EventArgs e)
    {

        if (_state != ControllerState.PreparingToMove && _state != ControllerState.Moving)
        {
            Console.WriteLine($"[Контроллер]: MovingHandler вызван в неверном состоянии: {_state}. Ожидалось PreparingToMove или Moving.");
            return;
        }

        if (_state == ControllerState.PreparingToMove)
        {
            _state = ControllerState.Moving;
            Console.WriteLine("[Контроллер]: Кабина готова. Переход в Moving. Запуск движения.");

            if (_currentFloor == _target)
                TargetReached?.Invoke(this, EventArgs.Empty);
            else
                StartCabin?.Invoke(this, EventArgs.Empty);
        }
        else if (_state == ControllerState.Moving)
        {
            FloorPassedDisplay?.Invoke(_currentFloor);

            if (_currentFloor == _target)
                TargetReached?.Invoke(this, EventArgs.Empty);
            else
            {
                Console.WriteLine($"[Контроллер]: Лифт проезжает этаж {_currentFloor}. Цель: {_target}.");
                EvaluateAndUpdateTargetWhileActive();
                _currentFloor += (_direction == ElevatorMoveDirection.Up ? 1 : -1);

                CabinNextFloor?.Invoke(this, EventArgs.Empty);
            }
        }
    }

    // Обработчик состояния Arrived
    public void OnTargetReached(object? sender, EventArgs e)
    {
        if (_state != ControllerState.Moving)
            return;

        _state = ControllerState.Arrived;

        Console.WriteLine($"[Контроллер]: Прибыли на этаж {_currentFloor}. Переход в Arrived.");
        ArrivedAtFloorDisplay?.Invoke(_currentFloor, _floorStates[_currentFloor - 1] == RequestedDirection.Both ? _direction : (_floorStates[_currentFloor - 1] == RequestedDirection.Down ? ElevatorMoveDirection.Down : ElevatorMoveDirection.Up));
        HandleArriveOnFloor();

        Console.WriteLine("[Контроллер]: Запрос остановки кабины.");
        StopCabin?.Invoke(this, EventArgs.Empty);
    }

    // Обработчик состояния Idle
    public void OnCabinUnlockedAndReady(object? sender, EventArgs e)
    {
        if (_state != ControllerState.Arrived)
        {
            Console.WriteLine($"[Контроллер]: OnCabinUnlockedAndReady вызван в неверном состоянии: {_state}. Ожидалось Arrived.");
            return;
        }

        Console.WriteLine("[Контроллер]: Цикл обслуживания этажа завершен (двери закрыты, кабина разблокирована). Переход в Idle.");
        _state = ControllerState.Idle;

        int newLogicalTarget = FindBestTarget();
        if (newLogicalTarget == NoTarget)
            Console.WriteLine("[Контроллер]: Цель не найдена, остаемся Idle.");
        else
        {
            _target = newLogicalTarget + 1;
            _direction = FindDirection(_target);

            TargetFound?.Invoke(this, EventArgs.Empty);
        }
    }

    // Обработчик состояния PreparingToMove
    private void OnTargetFound(object? sender, EventArgs e)
    {
        if (_state != ControllerState.GotTargetFromCabin && 
            _state != ControllerState.GotTargetFromFloor && 
            _state != ControllerState.Idle)
        {
            Console.WriteLine($"[Контроллер]: OnTargetFound вызван в неверном состоянии: {_state}. Ожидалось GotTargetFromCabin или GotTargetFromFloor.");
            return;
        }

        Console.WriteLine($"[Контроллер]: Цель найдена: {_target} ({_translations[_direction]}). Переход в PreparingToMove.");
        _state = ControllerState.PreparingToMove;

        PrepareCabin?.Invoke(this, EventArgs.Empty);
    }

    // Обработчик состояния GotTargetFromFloor
    public void OnNewTargetFromFloor(int floor, RequestedDirection dir)
    {
        if (_state != ControllerState.Idle && _state != ControllerState.PreparingToMove &&
            _state != ControllerState.Moving && _state != ControllerState.Arrived)
        {
            Console.WriteLine($"[Контроллер]: OnNewTargetFromFloor вызван из некорректного состояния: {_state}");
            return;
        }

        if (floor < 0 || floor >= FloorAmount)
            return;

        Console.WriteLine($"[Контроллер]: Новый вызов с этажа: {floor + 1}, направление: {dir}");

        UpdateFloorState(floor, dir);
        if (_state == ControllerState.Idle)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}, ищем новую цель.");

            int newLogicalTarget = FindBestTarget();
            if (newLogicalTarget == NoTarget)
                Console.WriteLine("[Контроллер]: Цель не найдена, остаемся Idle.");
            else
            {
                _target = newLogicalTarget + 1;
                _direction = FindDirection(_target);

                _state = ControllerState.GotTargetFromFloor;

                TargetFound?.Invoke(this, EventArgs.Empty);
            }
        }
        else if (_state == ControllerState.PreparingToMove || _state == ControllerState.Moving)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}, оцениваем релевантность новой цели.");
            EvaluateAndUpdateTargetWhileActive();
        }
        else if (_state == ControllerState.Arrived)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}. Новые вызовы учтены, но движение начнется после закрытия дверей и готовности кабины.");
        }
    }

    // Обработчик состояния GotTargetFromCabin
    public void OnNewTargetFromCabin(int floor)
    {
        if (_state != ControllerState.Idle && _state != ControllerState.PreparingToMove &&
            _state != ControllerState.Moving && _state != ControllerState.Arrived)
        {
            Console.WriteLine($"[Контроллер]: OnNewTargetFromCabin вызван из некорректного состояния: {_state}");
            return;
        }

        if (floor < 0 || floor >= FloorAmount)
            return;

        Console.WriteLine($"[Контроллер]: Новый вызов из кабины на этаж: {floor + 1}");
        ElevatorMoveDirection dirToTargetFloor = FindDirection(floor + 1);
        RequestedDirection wantedDir = _relationships[dirToTargetFloor];

        UpdateFloorState(floor, wantedDir);

        if (_state == ControllerState.Idle)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}, ищем новую цель.");

            int newLogicalTarget = FindBestTarget();
            if (newLogicalTarget == NoTarget)
                Console.WriteLine("[Контроллер]: Цель не найдена, остаемся Idle.");
            else
            {
                _target = newLogicalTarget + 1;
                _direction = FindDirection(_target);

                _state = ControllerState.GotTargetFromCabin;

                TargetFound?.Invoke(this, EventArgs.Empty);
            }
        }
        else if (_state == ControllerState.PreparingToMove || _state == ControllerState.Moving)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}, оцениваем релевантность новой цели.");
            EvaluateAndUpdateTargetWhileActive();
        }
        else if (_state == ControllerState.Arrived)
        {
            Console.WriteLine($"[Контроллер]: Состояние {_state}. Новые вызовы учтены, но движение начнется после закрытия дверей и готовности кабины.");
        }
    }

    // =============================================================

    private void EvaluateAndUpdateTargetWhileActive()
    {
        int currentTargetLogical = _target - 1;
        int potentialNewLogicalTarget = FindBestTarget();

        if (potentialNewLogicalTarget == NoTarget || potentialNewLogicalTarget == currentTargetLogical)
        {
            Console.WriteLine("[Контроллер]: Новая информация о вызовах не изменила текущую цель.");
            return;
        }

        bool newTargetIsBetter = false;
        if (_direction == ElevatorMoveDirection.Up && 
            ((potentialNewLogicalTarget + 1) < _target || 
            (_floorStates[_target] != _relationships[_direction] && 
            _floorStates[potentialNewLogicalTarget] == _relationships[_direction])) && 
            (potentialNewLogicalTarget + 1) > _currentFloor)
        {
            newTargetIsBetter = IsValidTargetForCurrentDirection(potentialNewLogicalTarget);
        }
        else if (_direction == ElevatorMoveDirection.Down && 
            ((potentialNewLogicalTarget + 1) > _target || 
            (_floorStates[_target] != _relationships[_direction] && 
            _floorStates[potentialNewLogicalTarget] == _relationships[_direction])) && 
            (potentialNewLogicalTarget + 1) < _currentFloor)
        {
            newTargetIsBetter = IsValidTargetForCurrentDirection(potentialNewLogicalTarget);
        }

        if (newTargetIsBetter)
        {
            Console.WriteLine($"[Контроллер]: Обнаружена более приоритетная промежуточная цель: {potentialNewLogicalTarget + 1}. Старая цель: {_target}.");
            _target = potentialNewLogicalTarget + 1;
        }
        else
        {
            Console.WriteLine($"[Контроллер]: Новый вызов ({potentialNewLogicalTarget + 1}) зарегистрирован, но текущая цель ({_target}) остается приоритетной или он не по пути.");
        }
    }

    private void HandleArriveOnFloor()
    {
        int floorIndex = _currentFloor - 1;
        if (floorIndex < 0 || floorIndex >= FloorAmount || _floorStates[floorIndex] == RequestedDirection.None)
            return;

        Console.WriteLine($"[Контроллер]: Обработка прибытия на этаж {_currentFloor}. Запрос: {_floorStates[floorIndex]}");

        if (_floorStates[floorIndex] == RequestedDirection.Both)
        {
            Console.WriteLine($"[Контроллер]: Запрос на этаже {_currentFloor} в направлении {_translations[_direction]} выполнен.");
            _floorStates[floorIndex] = (_direction == ElevatorMoveDirection.Up) ? RequestedDirection.Down : RequestedDirection.Up;
            Console.WriteLine($"[Контроллер]: На этаже {_currentFloor} остался запрос: {_floorStates[floorIndex]}");
        }
        else
        {
            Console.WriteLine($"[Контроллер]: Запрос на этаже {_currentFloor} в направлении {_floorStates[floorIndex]} выполнен.");
            _direction = _floorStates[floorIndex] == RequestedDirection.Down ? ElevatorMoveDirection.Down : ElevatorMoveDirection.Up;
            _floorStates[floorIndex] = RequestedDirection.None;
        }
    }

    private ElevatorMoveDirection FindDirection(int targetFloor)
    {
        if (_currentFloor < targetFloor) return ElevatorMoveDirection.Up;
        if (_currentFloor > targetFloor) return ElevatorMoveDirection.Down;
        return ElevatorMoveDirection.Up;
    }

    private int FindBestTarget()
    {
        int target = NoTarget;

        if (_direction != ElevatorMoveDirection.None)
        {
            int step = (_direction == ElevatorMoveDirection.Up) ? 1 : -1;
            for (int i = _currentFloor - 1 + step; i >= 0 && i < FloorAmount; i += step)
            {
                if (IsValidTargetForCurrentDirection(i, _direction))
                {
                    target = i;
                    break;
                }
            }
        }

        ElevatorMoveDirection oppositeDirection;

        if (_direction == ElevatorMoveDirection.None)
            oppositeDirection = ElevatorMoveDirection.None;
        else if (_direction == ElevatorMoveDirection.Down)
            oppositeDirection = ElevatorMoveDirection.Up;
        else
            oppositeDirection = ElevatorMoveDirection.Down;

        if (target == NoTarget)
        {
            int minDistance = FloorAmount + 1;
            for (int i = 0; i < FloorAmount; i++)
            {
                if (_floorStates[i] != RequestedDirection.None)
                {
                    int distance = Math.Abs((_currentFloor - 1) - i);
                    if (distance < minDistance)
                    {
                        if (target != NoTarget)
                            if (_floorStates[target] == _relationships[oppositeDirection] && _floorStates[i] != _relationships[oppositeDirection])
                                continue;

                        minDistance = distance;
                        target = i;
                    }
                }
            }
        }
        return target;
    }

    private bool IsValidTargetForCurrentDirection(int floor, ElevatorMoveDirection? forcedDirection = null)
    {
        ElevatorMoveDirection dirToCheck = forcedDirection ?? _direction;

        if (dirToCheck == ElevatorMoveDirection.None)
            return _floorStates[floor] != RequestedDirection.None;

        return _floorStates[floor] != RequestedDirection.None &&
               (_floorStates[floor] == RequestedDirection.Both ||
                _floorStates[floor] == _relationships[dirToCheck]);
    }

    private void UpdateFloorState(int floor, RequestedDirection dir)
    {
        if (_floorStates[floor] == RequestedDirection.None)
            _floorStates[floor] = dir;
        else if (_floorStates[floor] != dir)
            _floorStates[floor] = RequestedDirection.Both;
    }
}