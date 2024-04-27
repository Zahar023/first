using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_07
{
    internal class BreakingNews : News
    {
        public string Title { get; }
        public string Content { get; }

        public BreakingNews(string title, string content)
        {
            Title = title;
            Content = content;
        }

    }
}
