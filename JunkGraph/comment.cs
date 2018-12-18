using Microsoft.Win32;
using System;

//used to add printf and etc to the comment codes.
//aimed to re-use the comment you typed.
//usage: cat SqList.cpp | ./comment > comments.txt
public class main{
	static void Main(){
		string a;
		while((a = Console.ReadLine()) != null){
			a.Trim();
			if(a.Length < 2) continue;
			if((a[0] == '/' && a[1] == '*') || a[0] == '*'){
				if(a[0] == '*' && a[1] == '/'){
					Console.WriteLine("printf(\"please enter the id of the graph:\");");
				    Console.WriteLine("scanf(\"%d\", &graph_index);\n");
				}
				
				else
				Console.WriteLine("printf(\"" + a + "\\n\");");
				
			}

		}
	}
}