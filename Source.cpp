#include <iostream>
#include "persistent.h"

int main()
{
    int arr[6] = { 100,200,300,400,500,600 };
    std::string indxs[6] = { "a","b","c","d","e","f" };
    int size = sizeof(arr) / sizeof(arr[0]);

    PersistentArray<double> intArray(5);

    intArray.setElementToBase(0, 10.1);
    intArray.setElementToBase(1, 20.2);
    intArray.setElementToBase(2, 30.3);
    intArray.setElementToBase(3, 40.4);
    intArray.setElementToBase(4, 50.5);

    std::cout << "\nintArray.addVersion(0, 4, 999):\n";
    intArray.addVersion(0, 4, 999);
    std::cout << "\nintArray.addVersion(1, 3, 222):\n";
    intArray.addVersion(1, 3, 222);

    std::cout << "\nintArray.printAllVersions():\n";
    intArray.printAllVersions();

    std::cout << "\nintArray.changeVersion(0, 2, -333.3)\n";
    intArray.changeVersion(0, 2, -333.3);

    std::cout << "\nintArray.printAllVersions():\n";
    intArray.printAllVersions();

    std::cout << "\nintArray.deleteElement(2, 0):\n";
    intArray.deleteElement(2, 0);

    std::cout << "\nintArray.printAllVersions():\n";
    intArray.printAllVersions();

    std::cout << "\nintArray.insertElement(2, 0, 666.6):\n";
    intArray.insertElement(2, 0, 666.6);
    std::cout << "\nintArray.insertElement(2, 1, 555.5):\n";
    intArray.insertElement(2, 1, 555.5);

    std::cout << "\nintArray.printAllVersions():\n";
    intArray.printAllVersions();

    std::cout << "\n==================================\n";

    PersistentArray<int> intArray2(arr, size);

    std::cout << "\nintArray2.printAllVersions():\n";
    intArray2.printAllVersions();

    std::cout << "\n===================================================================\n";

    PersistentDoublyLinkedList<double> dll(10.1);
    dll.append(20.2);
    dll.append(30.3);
    dll.append(40.4);
    dll.append(50.5);
    dll.append(60.6);

    std::cout << "\ndll.addVersion(0, 5, 999.):\n";
    dll.addVersion(0, 5, 999.);
    std::cout << "\ndll.addVersion(1, 3, 222.):\n";
    dll.addVersion(1, 3, 222.0);

    std::cout << "\ndll.printAllVersions():\n";
    dll.printAllVersions();

    std::cout << "\nchangeVersion(1, 3, -333.):\n";
    dll.changeVersion(1, 3, -333.);

    std::cout << "\ndll.printAllVersions():\n";
    dll.printAllVersions();

    std::cout << "\ndll.deleteElement(1, 3):\n";
    dll.deleteElement(1, 3);

    std::cout << "\ndll.printAllVersions():\n";
    dll.printAllVersions();

    std::cout << "\ndll.insertElement(2, 0, 666):\n";
    dll.insertElement(2, 0, 666);

    std::cout << "\ndll.printAllVersions():\n";
    dll.printAllVersions();

    std::cout << "\n\n==================================\n";

    PersistentDoublyLinkedList<int> dll2(arr, size);

    std::cout << "\ndll2.addVersion(0, 5, 999):\n";
    dll2.addVersion(0, 5, 999);
    std::cout << "\ndll2.addVersion(1, 3, 222):\n";
    dll2.addVersion(1, 3, 222);

    std::cout << "\ndll2.printAllVersions():\n";
    dll2.printAllVersions();

    std::cout << "\ndll2.changeVersion(1, 3, -333):\n";
    dll2.changeVersion(1, 3, -333);

    std::cout << "\ndll2.printAllVersions():\n";
    dll2.printAllVersions();

    std::cout << "\n===================================================================\n";

    PersistentAssociativeArray<std::string, double> aa("Name", 10.1);
    aa.setElementToBase("Age", 20.2);
    aa.setElementToBase("Height", 30.3);
    aa.setElementToBase("Weight", 40.4);
    aa.setElementToBase("IQ", 50.5);
    aa.setElementToBase("Children", 60.6);

    std::cout << "\naa.addVersion(0, \"IQ\", 999.9):\n";
    aa.addVersion(0, "IQ", 999.9);
    std::cout << "\naa.addVersion(1, \"AGE\", 222.2):\n";
    aa.addVersion(1, "Age", 222.2);

    std::cout << "\naa.printAllVersions():\n";
    aa.printAllVersions();

    std::cout << "\naa.changeVersion(1, \"Weight\", -333.3):\n";
    aa.changeVersion(1, "Weight", -333.3);

    std::cout << "\naa.printAllVersions():\n";
    aa.printAllVersions();

    std::cout << "\naa.insertElement(2, 0, \"smth1\", 666):\n";
    aa.insertElement(2, 0, "smth1", 666);
    std::cout << "\naa.insertElement(2, 1, \"smth2\", 555):\n";
    aa.insertElement(2, 1, "smth2", 555);
    std::cout << "\naa.insertElement(4, 0, \"smth3\", 777):\n";
    aa.insertElement(4, 0, "smth3", 777);

    std::cout << "\naa.printAllVersions():\n";
    aa.printAllVersions();

    std::cout << "\naa.deleteElement(2, \"Height\"):\n";
    aa.deleteElement(2, "Height");

    std::cout << "\naa.printAllVersions():\n";
    aa.printAllVersions();

    std::cout << "\n==================================\n\n";

    PersistentAssociativeArray< std::string, int> aa2(indxs, arr, size);

    std::cout << "\naa2.addVersion(0, \"d\", 999):\n";
    aa2.addVersion(0, "d", 999);
    std::cout << "\naa2.addVersion(1, \"c\", 222):\n";
    aa2.addVersion(1, "c", 222);

    std::cout << "\naa2.printAllVersions():\n";
    aa2.printAllVersions();

    std::cout << "\naa2.changeVersion(1, \"c\", -333):\n";
    aa2.changeVersion(1, "c", -333);
    std::cout << "\naa2.changeVersion(2, \"c\", -333):\n";
    aa2.changeVersion(2, "c", -333);

    std::cout << "\naa2.printAllVersions():\n";
    aa2.printAllVersions();

    std::cout << "\naa2.deleteElement(1, \"c\"):\n";
    aa2.deleteElement(1, "c");

    std::cout << "\naa2.printAllVersions():\n";
    aa2.printAllVersions();

    std::cout << "\naa2.deleteElement(3, \"d\"):\n";
    aa2.deleteElement(3, "d");

    std::cout << "\naa2.printAllVersions():\n";
    aa2.printAllVersions();

    std::cout << "\n===================================================================\n";

    std::cout << "\nFrom DLL (dll[3]) to Arr:\n";
    PersistentArray<double> converted_array1 = Convert<double>::toArray(dll.getVersion(3));
    std::cout << "converted_array1.printAllVersions():\n"; 
    converted_array1.printAllVersions();
    std::cout << "dll.printAllVersions():\n";
    dll.printAllVersions();

    std::cout << "\nFrom AA (aa2[4]) to Arr:\n";
    PersistentArray<int> converted_array2 = Convert<int>::toArray(aa2.getVersion(4));
    std::cout << "converted_array2.printAllVersions():\n";
    converted_array2.printAllVersions();
    std::cout << "aa2.printAllVersions():\n";
    aa2.printAllVersions();

    std::cout << "\nFrom Arr (intArray[4]) to DLL:\n";
    PersistentDoublyLinkedList<double> converted_list1 = Convert<double>::toDLList(intArray.getVersion(4));
    std::cout << "converted_list1.printAllVersions():\n";
    converted_list1.printAllVersions();
    std::cout << "intArray.printAllVersions():\n";
    intArray.printAllVersions();

    std::cout << "\nFrom AA (aa[2]) to DLL:\n";
    PersistentDoublyLinkedList<double> converted_list2 = Convert<double>::toDLList(aa.getVersion(2));
    std::cout << "converted_list2.printAllVersions():\n";
    converted_list2.printAllVersions();
    std::cout << "aa.printAllVersions():\n";
    aa.printAllVersions();
    
    std::cout << "\nFrom Arr(intArray2[0]) to AA:\n";
    std::string  keys1[] = { "first", "second", "third", "fourth", "fifth", "sixth" };
    PersistentAssociativeArray<std::string, int> converted_aa1 = Convert<int>::toAssociativeArray(intArray2.getVersion(0), keys1);
    std::cout << "converted_aa1.printAllVersions():\n";
    converted_aa1.printAllVersions();
    std::cout << "intArray.printAllVersions():\n";
    intArray2.printAllVersions();

    std::cout << "\nFrom DLL(dll2[2]) to AA:\n";
    double keys2[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    PersistentAssociativeArray<double, int> converted_aa2 = Convert<int>::toAssociativeArray(dll2.getVersion(2), keys2);
    std::cout << "converted_aa2.printAllVersions():\n";
    converted_aa2.printAllVersions();
    std::cout << "dll2.printAllVersions():\n";
    dll2.printAllVersions();


    return 0;
}