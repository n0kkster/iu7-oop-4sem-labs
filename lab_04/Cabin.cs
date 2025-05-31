namespace OOP_LAB_04;
public class Cabin
{
    public enum CabinState
    {
        Idle,
        Unlocked,
        Locked,
        ReadyToMove,
        Moving,
        BoardingStarted,
        BoardingCompleted
    }

    private CabinState _state = CabinState.Unlocked;
    private readonly Doors _doors = new();

    public event EventHandler? CabinReadyToMove;
    public event EventHandler? CabinFloorPassed;
    public event EventHandler? CabinUnlocked;

    public event EventHandler? OpenDoors;
    public event EventHandler? CloseDoors;
    public event EventHandler? Lock;

    public Cabin()
    {
        _doors.DoorsClosed += OnDoorsClosed;
        _doors.DoorsOpened += OnDoorsOpened;

        OpenDoors += _doors.OpenAsync;
        CloseDoors += _doors.CloseAsync;
        Lock += OnLock;
    }

    public void PrepareToMove(object? sender, EventArgs e)
    {
        if (_state != CabinState.Unlocked)
            return;

        _state = CabinState.ReadyToMove;
        Console.WriteLine("[Кабина]: готова к движению!");
        CabinReadyToMove?.Invoke(this, EventArgs.Empty);
    }

    public void Move(object? sender, EventArgs e)
    {
        if (_state != CabinState.ReadyToMove && _state != CabinState.Moving)
            return;

        if (_state == CabinState.ReadyToMove)
        {
            _state = CabinState.Moving;
            Console.WriteLine("[Кабина]: начинает движение...");
        }
        _ = ContinueMovementAsync();
    }

    private async Task ContinueMovementAsync()
    {
        await Task.Delay(Config.FloorPassDelay);
        Console.WriteLine("[Кабина]: проехала этаж");
        CabinFloorPassed?.Invoke(this, EventArgs.Empty);
    }

    public void StopMovement(object? sender, EventArgs e)
    {
        if (_state != CabinState.Moving && _state != CabinState.ReadyToMove)
            return;

        _state = CabinState.Idle;
        Console.WriteLine("[Кабина]: остановилась");
        Lock?.Invoke(this, EventArgs.Empty);
    }

    public void OnLock(object? sender, EventArgs e)
    {
        if (_state != CabinState.Idle && _state != CabinState.Unlocked)
            return;

        _state = CabinState.Locked;
        Console.WriteLine("[Кабина]: Движение заблокировано");

        OpenDoors?.Invoke(this, EventArgs.Empty);
    }

    private async void OnDoorsOpened(object? sender, EventArgs e)
    {
        if (_state != CabinState.Locked)
            return;

        _state = CabinState.BoardingStarted;
        Console.WriteLine("[Кабина]: Посадка начата. Ожидаем пассажиров.");
        await RunTimerAsync(Config.BoardingTime, BoardingCompleted);
    }

    private void OnDoorsClosed(object? sender, EventArgs e)
    {
        if (_state != CabinState.BoardingCompleted)
            return;

        _state = CabinState.Unlocked;
        Console.WriteLine("[Кабина]: Движение разблокировано.");
        CabinUnlocked?.Invoke(this, EventArgs.Empty);
    }

    private void BoardingCompleted()
    {
        if (_state != CabinState.BoardingStarted)
            return;

        _state = CabinState.BoardingCompleted;
        Console.WriteLine("[Кабина]: Посадка окончена.");
        CloseDoors?.Invoke(this, EventArgs.Empty);
    }

    private async Task RunTimerAsync(TimeSpan delay, Action callback)
    {
        await Task.Delay(delay);
        callback?.Invoke();
    }
}
