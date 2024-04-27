using Avalonia.Controls;
using MVVM_Lab_8.ViewModels;

namespace MVVM_Lab_8.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DataContext = new MainWindowViewModel();
        }
    }
}