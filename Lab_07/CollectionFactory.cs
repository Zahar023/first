using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    public class CollectionFactory
    {
        public IObservable<NotifyCollectionChangedEventArgs> GetCollectionChanges(ObservableCollection<Users> collection)
        {
            return new CollectionChangesObservable(collection);
        }
    }
}
