namespace OOP_LAB_04;
public class Doors
{
    public enum DoorsState
    {
        Closed,
        Closing,
        Opened,
        Opening,
    }

    private DoorsState _state = DoorsState.Closed;

    public event EventHandler? DoorsClosed;
    public event EventHandler? DoorsOpened;

    public async void OpenAsync(object? sender, EventArgs e)
    {
        if (_state != DoorsState.Closed)
            return;

        _state = DoorsState.Opening;
        Console.WriteLine("[Двери]: Открываются..");
        await RunTimerAsync(Config.OpenCloseDelay, DoorsOpeningCompleted);
    }

    private void DoorsOpeningCompleted()
    {
        if (_state != DoorsState.Opening)
            return;

        _state = DoorsState.Opened;
        Console.WriteLine("[Двери]: Открыты");
        DoorsOpened?.Invoke(this, EventArgs.Empty);
    }

    public async void CloseAsync(object? sender, EventArgs e)
    {
        if (_state != DoorsState.Opened)
            return;

        _state = DoorsState.Closing;
        Console.WriteLine("[Двери]: Закрываются..");
        await RunTimerAsync(Config.OpenCloseDelay, DoorsClosingCompleted);
    }

    private void DoorsClosingCompleted()
    {
        if (_state != DoorsState.Closing)
            return;

        _state = DoorsState.Closed;
        Console.WriteLine("[Двери]: Закрыты");
        DoorsClosed?.Invoke(this, EventArgs.Empty);
    }
    private async Task RunTimerAsync(TimeSpan delay, Action callback)
    {
        await Task.Delay(delay);
        callback?.Invoke();
    }
}