#include <iostream>
using namespace std;

// const int inputs_size = 2;
// const char inputs[] = {'b', 'c'};
const int inputs_size = 4;
const char inputs[] = {'a', 'a', 'b', 'c'};

// This won't work, unless you declare 'i' as global
// bool input_ended()
// {
	// return i >= inputs_size;
// }

/*
 * Gets next inputs, or 'x' if no inputs available.
 * WARNING: this function shifts the input, once you call it!
 */
char next()
{
	//TODO add logics to return 'x'
	static int i = 0; // 'i' doesn't get re-initialized every time we enter this func, as it's marked STATIC
	return inputs[i++];
}

int main()
{
	cout << "Next input word is " << next() << endl;
	cout << "Next input word is " << next() << endl;
/*
	int state = 0;
	
	while(1)
	{
		c = next();
		switch(state)
		{
			case 2:
				if(c != 'a') // You can avoid goto...
					goto error;
				else
					state = 0;
				break;
			default:
				break;
		}
	}
	
	return 0;
   
error:
	cout << "ERROR!" << endl;
	cout << "Input " + c + " not legal in state " + state << endl;
	return -1;
*/
}