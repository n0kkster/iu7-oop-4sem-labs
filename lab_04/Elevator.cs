namespace OOP_LAB_04;
public class Elevator
{
    private readonly Cabin _cabin = new();
    private readonly Controller _controller = new();

    private readonly MainWindow _parent;

    public event Action<int>? NewTargetFromCabin;
    public event Action<int, RequestedDirection>? NewTargetFromFloor;

    public Elevator(MainWindow parent)
    {
        _parent = parent;

        Console.WriteLine("Лифт стоит на 1 этаже.");
        Console.WriteLine("Кабина готова к движению. Двери закрыты.");

        NewTargetFromCabin += _controller.OnNewTargetFromCabin;
        NewTargetFromFloor += _controller.OnNewTargetFromFloor;

        _controller.StartCabin += _cabin.Move;
        _controller.StopCabin += _cabin.StopMovement;
        _controller.PrepareCabin += _cabin.PrepareToMove;
        _controller.CabinNextFloor += _cabin.Move;
        _controller.OpenCabin += _cabin.OnLock;

        _controller.ArrivedAtFloorDisplay += _parent.ArrivedOnFloor;
        _controller.FloorPassedDisplay += _parent.SetFloorDisplayNumber;

        _cabin.CabinReadyToMove += _controller.MovingHandler;
        _cabin.CabinFloorPassed += _controller.MovingHandler;
        _cabin.CabinUnlocked += _controller.OnCabinUnlockedAndReady;
    }

    public void OnNewTargetFromCabin(int floor)
    {
        NewTargetFromCabin?.Invoke(floor - 1);
    }

    public void OnNewTargetFromFloor(int floor, RequestedDirection direction)
    {
        NewTargetFromFloor?.Invoke(floor - 1, direction);
    }
}
