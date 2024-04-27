using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using System.Windows.Input;

namespace MVVMLab9.Control
{
    public class CustomControl : TemplatedControl
    {
        public static readonly StyledProperty<bool> IsGridVisibleProperty =
            AvaloniaProperty.Register<CustomControl, bool>(nameof(IsGridVisible), false);

        public bool IsGridVisible
        {
            get => GetValue(IsGridVisibleProperty);
            set => SetValue(IsGridVisibleProperty, value);
        }

        public static readonly StyledProperty<string> SliderOrientationProperty =
            AvaloniaProperty.Register<CustomControl, string>(nameof(SliderOrientation), "Horizontal");

        public string SliderOrientation
        {
            get => GetValue(SliderOrientationProperty);
            set => SetValue(SliderOrientationProperty, value);
        }

        public static readonly StyledProperty<ICommand> OrientationIconClickCommandProperty =
            AvaloniaProperty.Register<CustomControl, ICommand>("False");

        public ICommand OrientationIconClickCommand
        {
            get => GetValue(OrientationIconClickCommandProperty);
            set
            {
                SetValue(OrientationIconClickCommandProperty, value);
                if (SliderOrientation == "Horizontal")
                    SliderOrientation = "Vertical";
                else
                    SliderOrientation = "Horizontal";
            }
        }

        public static readonly StyledProperty<ICommand> IconClickCommandProperty =
            AvaloniaProperty.Register<CustomControl, ICommand>("False");

        public ICommand IconClickCommand
        {
            get => GetValue(IconClickCommandProperty);
            set {
                SetValue(IconClickCommandProperty, value);
                if (IsGridVisible == true)
                    IsGridVisible = false;
                else
                    IsGridVisible = true;
            }
        }

        public bool isOpen { get; set; }

        public static string SetNewCondition(string isOpen)
        {
            if (isOpen == "True")
            {
                return "False";
            }
            return "True";
        }

        public string SetNewOrientation(string orientation)
        {
            if (orientation == "Vertical")
            {
                return "Horizontal";
            }
            return "Vertical";
        }
    }
}
