using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Media;
using ReactiveUI;
using System.Drawing;
using Avalonia.Skia.Helpers;
using PalitraMVVM.Models;
using System.IO;


namespace PalitraMVVM.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        public Bitmap bitmap;
        public Avalonia.Media.Imaging.Bitmap b { get; set; }
        public System.Drawing.Bitmap bs;
        public SolidColorBrush Color { get; set; }

        public Avalonia.Media.Imaging.Bitmap Bitm { get; set; }
        public MainWindowViewModel()
        {
            b = new Avalonia.Media.Imaging.Bitmap("C:\\Users\\zahar\\source\\repos\\PalitraMVVM\\Assets\\color-space (1).jpg");
            Bitm = new Avalonia.Media.Imaging.Bitmap("C:\\Users\\zahar\\source\\repos\\PalitraMVVM\\Assets\\color-space (1).jpg");
            Color = new SolidColorBrush(Avalonia.Media.Color.FromArgb(255, 1, 1, 1));
        }

        public Canvas Canvas;
        
        public string Results { get; set; }

        public void PointerPressedHandler2(object sender, PointerPressedEventArgs args)
        {
            var point = args.GetCurrentPoint(sender as Avalonia.Controls.Control);
            var x = point.Position.X;
            var y = point.Position.Y;

            var msg = $"Pointer press at {x}, {y} relative to sender.";
            if (point.Properties.IsLeftButtonPressed)
            {
                msg += " Left button pressed.";
            }
            if (point.Properties.IsRightButtonPressed)
            {
                msg += " Right button pressed.";
            }
            MemoryStream stream = new MemoryStream();
            b.Save(stream);
            bs = new System.Drawing.Bitmap(stream);
            var pixel = bs.GetPixel((int)x, (int)y);
            byte red = pixel.R;
            byte green = pixel.G;
            byte blue = pixel.B;

            Avalonia.Media.Color col = Avalonia.Media.Color.FromArgb(255, red, green, blue);
            Color = new SolidColorBrush(col);

            Results = msg;
        }
        public string Greeting => "Welcome to Avalonia!";
        public string Canv => "Welcome to Avalonia!";

    }
}
