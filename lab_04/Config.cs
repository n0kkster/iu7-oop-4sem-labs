namespace OOP_LAB_04;
public static class Config
{
    public static TimeSpan BoardingTime { get { return TimeSpan.FromSeconds(3); } }
    public static TimeSpan OpenCloseDelay { get { return TimeSpan.FromSeconds(1.5); } }
    public static TimeSpan FloorPassDelay { get { return TimeSpan.FromSeconds(1.5); } }
}
