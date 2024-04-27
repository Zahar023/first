using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Media;
using Avalonia.Platform;

namespace PalitraMVVM.Control
{
    public class CellControl : TemplatedControl
    {
        public static readonly StyledProperty<SolidColorBrush> NewColorProperty =
            AvaloniaProperty.Register<CellControl, SolidColorBrush>(nameof(NewColor), new SolidColorBrush(Avalonia.Media.Color.FromArgb(255, 0, 0, 0)));

        public SolidColorBrush NewColor
        {
            get => GetValue(NewColorProperty);
            set => SetValue(NewColorProperty, value);
        }
    }
}
