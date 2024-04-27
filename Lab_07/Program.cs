using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace Lab_07;

class Program
{
    static void Main()
    {
        CollectionFactory factory = new CollectionFactory();
        ObservableCollection<Users> collection = new ObservableCollection<Users>();

        IObservable<NotifyCollectionChangedEventArgs> changes = factory.GetCollectionChanges(collection);
        changes.Subscribe(new LoggerObserver());

        Users firstUser = new Users("Alex", 20);
        Users secondUser = new Users("Bilbo", 24);
        Users firdUser = new Users("Petr", 40);
        
        collection.Add(firstUser);
        collection.Add(secondUser);
        collection.Add(firdUser);
        collection.Remove(secondUser);
    }
}