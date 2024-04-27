using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    internal class NewsAggregator : IObservable<News>
    {
        private List<IObserver<News>> observers;
        
        public NewsAggregator()
        {
            observers = new List<IObserver<News>>();
        }
        public IDisposable Subscribe(IObserver<News> observer)
        {
            observers.Add(observer);

            return null;
        }

        public void Notify(News news)
        {
            foreach (IObserver<News> observer in observers)
            {
                observer.OnNext(news);
            }
        }
        
    }
}
