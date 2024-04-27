using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    public class LoggerObserver : IObserver<NotifyCollectionChangedEventArgs>
    {
        public void OnNext(NotifyCollectionChangedEventArgs value)
        {
            if (value.Action == NotifyCollectionChangedAction.Add)
            {
                Users user = (Users)value.NewItems[0];

                File.AppendAllText("C:\\Users\\zahar\\source\\repos\\Lab_07\\log.txt",
                    $"AddUser: {value.NewItems?.Count}, Name: {user.Name}, Age {user.Age}\n");
                Console.WriteLine(
                    $"AddUser: {value.NewItems?.Count}, Name: {user.Name}, Age {user.Age}\n");
            }
            else if (value.Action == NotifyCollectionChangedAction.Remove)
            {
                Users user = (Users)value.OldItems[0];

                File.AppendAllText("C:\\Users\\zahar\\source\\repos\\Lab_07\\log.txt",
                    $"RemoveUser: {value.OldItems?.Count}, Name: {user.Name}, Age {user.Age}\n");
                Console.WriteLine(
                    $"RemoveUser: {value.OldItems?.Count}, Name: {user.Name}, Age {user.Age}");
            }
        }

        public void OnCompleted()
        {
        }

        public void OnError(Exception error)
        {
        }
    }
}
