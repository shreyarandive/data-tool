//    main.cpp : Defines the entry point for the console application.
//    author: Shreya Randive
//

#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "Datasource.h"
using namespace std;

int main()
{
    Datasource datasources;
    string input;
    int n = 1, total_datasources;
    
    cout << "Enter number of data sources: ";
    cin >> total_datasources;
    
    while (n <= total_datasources)
    {
        cout << "Enter filename for data source " << n << ": ";
        cin >> input;
        if(datasources.addFilename(input))
            n++;
    }
    
    cout << endl;
    
    while (1)
    {
        cout << "Enter operation ('N' to exit): ";
        cin >> input;
        
        if (input == "N" || input == "n")
            break;
        
        datasources.executeOperation(input);
    }
    
    return 0;
}
