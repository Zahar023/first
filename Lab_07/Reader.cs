using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    internal sealed class Reader : IObserver<News>
    {
        public string Name { get; }

        public Reader(string name)
        {
            Name = name;
        }
        public void OnCompleted()
        {
            throw new NotImplementedException();
        }

        public void OnError(Exception error)
        {
            throw new NotImplementedException();
        }

        public void OnNext(News observer)
        {
            Console.WriteLine(Name);
            Console.WriteLine(observer.Title);
            Console.WriteLine(observer.Content);
            Console.WriteLine("----------------");
            Console.WriteLine();
        }
    }
}
