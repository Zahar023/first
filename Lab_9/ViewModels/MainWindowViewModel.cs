using MVVMLab9.Views;
using ReactiveUI;
using System.ComponentModel;
using System.Reactive;
using System.Security.Cryptography.X509Certificates;

namespace MVVMLab9.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    { 
        private bool _isGridVisible = true;
        private string _sliderOrientation = "Horizontal";
        public string SliderOrientation
        {
            get => _sliderOrientation;
            set => this.RaiseAndSetIfChanged(ref _sliderOrientation, value);
        }

        public bool IsGridVisible
        {
            get => _isGridVisible;
            set => this.RaiseAndSetIfChanged(ref _isGridVisible, value);
        }

        public void CreatingCommandOrientation(string msg)
        {
            if (SliderOrientation == "Horizontal")
                SliderOrientation = "Vertical";
            else
                SliderOrientation = "Horizontal";
        }
        public void CreatingCommand(string msg)
        {
            if (IsGridVisible == true)
                IsGridVisible = false;
            else
                IsGridVisible = true;
        }

        public MainWindowViewModel()
        {          
            ButtonCommand = ReactiveCommand.Create<string>(CreatingCommand);
            ButtonCommandOrientation = ReactiveCommand.Create<string>(CreatingCommandOrientation);
        }

        public ReactiveCommand<string, Unit> ButtonCommand { get; }
        public ReactiveCommand<string, Unit> ButtonCommandOrientation { get; }
    }
}
