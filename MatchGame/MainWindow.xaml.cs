using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MatchGame
{
    using System.Windows.Threading;
    public partial class MainWindow : Window
    {
        private DispatcherTimer _timer = new DispatcherTimer();
        private int _tenthsOfSecondsElapsed ;
        private int _matchesFound;
        private TextBlock _lastTextBlockClicked;
        private bool _findingMatch = false;
        public MainWindow()
        {
            InitializeComponent();
            _timer.Interval = TimeSpan.FromSeconds(.1);
            _timer.Tick += Timer_Tick;
            SetUpGame();
        }

        private void TimeTextBlock_MouseDown(object sender, EventArgs eventArgs)
        {
            if (_matchesFound == 8)
            {
                SetUpGame();
            }
        }

        

        private void Timer_Tick(object sender, EventArgs e)
        {
            _tenthsOfSecondsElapsed++;
            TimerTextBlock.Text = (_tenthsOfSecondsElapsed / 10F).ToString("0.0s");
            if (_matchesFound == 8)
            {
                _timer.Stop();
                TimerTextBlock.Text += "Play Again?";
            }
        }

        private void SetUpGame()
        {
            List<string> animalEmoji = new List<string>()
            {
                "🐵", "🐵",
                "🐶", "🐶",
                "🐱", "🐱",
                "🦝", "🦝",
                "🐮", "🐮",
                "🐷", "🐷",
                "🦒", "🦒",
                "🐻", "🐻",
            };

            Random random = new Random();

            foreach (TextBlock textBlock in MainGrid.Children.OfType<TextBlock>())
            {
                if (animalEmoji.Count != 0)
                {
                    int index = random.Next(animalEmoji.Count);
                    string animalText = animalEmoji[index];
                    textBlock.Text = animalText;
                    textBlock.Visibility = Visibility.Visible;
                    animalEmoji.RemoveAt(index);
                }
            }
            _timer.Start();
            _tenthsOfSecondsElapsed = 0;
            _matchesFound = 0;
        }

        public void TextBlock_MouseDown(object sender, MouseButtonEventArgs eventArgs)
        {
            TextBlock textBlock = (TextBlock)sender;
            if (_findingMatch == false)
            {
                textBlock.Visibility = Visibility.Hidden;
                _lastTextBlockClicked = textBlock;
                _findingMatch = true;
            } 
            else if (_lastTextBlockClicked.Text == textBlock.Text)
            {
                _matchesFound++;
                textBlock.Visibility = Visibility.Hidden;
                _findingMatch = false;
            }
            else
            {
                _lastTextBlockClicked.Visibility = Visibility.Visible;
                _findingMatch = false;
            }
        }
    }
}
