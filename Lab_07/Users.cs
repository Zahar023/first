using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    public class Users
    {
        public string Name { get; }
        public int Age { get; }

        public Users(string name, int age)
        {
            Name = name;
            Age = age;
        }
    }
}
