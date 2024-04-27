namespace MVVM_Lab_8.ViewModels
{
    public class MainWindowViewModel : BaseViewModel
    {
		private BaseViewModel _selectedViewModel = new FlatOutputViewModel();

		public BaseViewModel SelectedViewModel
        {
			get { return _selectedViewModel; }
			set { _selectedViewModel = value; }
		}

		public string Greeting => "Welcome to Avalonia!";

    }
}
