using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Media;
using Avalonia.Media.Imaging;
using Avalonia.Platform;
using System;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using Avalonia.VisualTree;
using SkiaSharp;

namespace PalitraMVVM.Views
{
    public partial class MainWindow : Window
    {
        public Avalonia.Media.Imaging.Bitmap b { get; set;}
        public System.Drawing.Bitmap bs;
        public SolidColorBrush Color { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            b = new Avalonia.Media.Imaging.Bitmap("C:\\Users\\zahar\\source\\repos\\PalitraMVVM\\Assets\\color-space (1).jpg");
        }
        
        private void PointerPressedHandler(object sender, PointerPressedEventArgs args)
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
            results.Text = msg;
            NewColor.Background = Color;
        }

    }
}