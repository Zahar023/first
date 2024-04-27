using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    public class CollectionChangesObservable : IObservable<NotifyCollectionChangedEventArgs>
    {
        private ObservableCollection<Users> _collection;

        public CollectionChangesObservable(ObservableCollection<Users> collection)
        {
            _collection = collection;
        }

        public IDisposable Subscribe(IObserver<NotifyCollectionChangedEventArgs> observer)
        {
            NotifyCollectionChangedEventHandler handler = (sender, e) => observer.OnNext(e);
            _collection.CollectionChanged += handler;

            return new Unsubscriber(_collection, handler);
        }
    }
}
