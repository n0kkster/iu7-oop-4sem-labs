using System.Windows;
using System.Windows.Media;

namespace OOP_LAB_04;
public partial class MainWindow : Window
{
    private readonly Elevator _elevator;

    public event Action<int>? NewTargetFromCabin;
    public event Action<int, RequestedDirection>? NewTargetFromFloor;

    public MainWindow()
    {
        InitializeComponent();
        _elevator = new(this);

        NewTargetFromCabin += _elevator.OnNewTargetFromCabin;
        NewTargetFromFloor += _elevator.OnNewTargetFromFloor;
    }

    public void SetFloorDisplayNumber(int floor)
    {
        FloorDisplay.Content = floor;
    }

    public void ArrivedOnFloor(int floor, ElevatorMoveDirection dir)
    {
        Console.WriteLine($"Arrivied on floor {floor} while moving {dir}");
        switch (floor)
        {

            case 1:
                CabinFloor1Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                Floor1UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                
                break;

            case 2:
                CabinFloor2Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor2UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor2DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 3:
                CabinFloor3Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor3UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor3DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 4:
                CabinFloor4Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor4UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor4DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 5:
                CabinFloor5Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor5UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor5DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 6:
                CabinFloor6Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor6UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor6DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 7:
                CabinFloor7Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor7UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor7DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 8:
                CabinFloor8Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                if (dir == ElevatorMoveDirection.Up)
                    Floor8UpBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));
                else
                    Floor8DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            case 9:
                CabinFloor9Btn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                //if (dir == ElevatorMoveDirection.Down)
                    Floor9DownBtn.Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF7C7C7C"));

                break;

            default:
                break;
        }
    }

    private void CabinFloor1Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor1Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(1);
    }

    private void CabinFloor2Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor2Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(2);
    }

    private void CabinFloor3Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor3Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(3);
    }

    private void CabinFloor4Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor4Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(4);
    }

    private void CabinFloor5Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor5Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(5);
    }

    private void CabinFloor6Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor6Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(6);
    }

    private void CabinFloor7Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor7Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(7);
    }

    private void CabinFloor8Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor8Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(8);
    }

    private void CabinFloor9Btn_Click(object sender, RoutedEventArgs e)
    {
        CabinFloor9Btn.Background = Brushes.LightGreen;

        NewTargetFromCabin?.Invoke(9);
    }

    private void Floor1UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor1UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(1, RequestedDirection.Up);
    }

    private void Floor2UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor2UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(2, RequestedDirection.Up);
    }

    private void Floor2DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor2DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(2, RequestedDirection.Down);
    }

    private void Floor3UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor3UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(3, RequestedDirection.Up);
    }

    private void Floor3DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor3DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(3, RequestedDirection.Down);
    }

    private void Floor4UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor4UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(4, RequestedDirection.Up);
    }

    private void Floor4DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor4DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(4, RequestedDirection.Down);
    }

    private void Floor5UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor5UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(5, RequestedDirection.Up);
    }

    private void Floor5DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor5DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(5, RequestedDirection.Down);
    }

    private void Floor6UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor6UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(6, RequestedDirection.Up);
    }

    private void Floor6DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor6DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(6, RequestedDirection.Down);
    }

    private void Floor7UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor7UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(7, RequestedDirection.Up);
    }

    private void Floor7DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor7DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(7, RequestedDirection.Down);
    }

    private void Floor8UpBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor8UpBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(8, RequestedDirection.Up);
    }

    private void Floor8DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor8DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(8, RequestedDirection.Down);
    }

    private void Floor9DownBtn_Click(object sender, RoutedEventArgs e)
    {
        Floor9DownBtn.Background = Brushes.LightGreen;

        NewTargetFromFloor?.Invoke(9, RequestedDirection.Down);
    }
}
