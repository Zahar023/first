using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    public class Unsubscriber : IDisposable
    {
        private ObservableCollection<Users> _collection;
        private NotifyCollectionChangedEventHandler _handler;

        public Unsubscriber(ObservableCollection<Users> collection, NotifyCollectionChangedEventHandler handler)
        {
            _collection = collection;
            _handler = handler;
        }

        public void Dispose()
        {
            if (_collection != null)
            {
                _collection.CollectionChanged -= _handler;
            }
        }
    }
}
