#include "MyPointers.h"
#include "Song.h"
#include <memory>
#include <iostream>

using namespace std;

// Using raw pointers -- not recommended.
void UseRawPointer()
{
	IMedia* pSong = new Song(L"Nothing on You", L"Bruno Mars");
	Song* pSong2 = new Song(L"Born in the USA", L"Bruce Springsteen");

	// Use pSong...
	pSong->playMedia();
	// Don't forget to delete!
	delete pSong;

	// Use pSong2...
	pSong2->printSong();
	pSong2->playMedia();
	// Don't forget to delete!
	delete pSong2;
}

// Using smart pointers -- recommended.
void UseSmartSharedPointer()
{
	// The first main type of Smart Pointer, is the Shared Pointer.
	// It’s a type of pointer that allows multiple pointers to refer to the same object.
	// Shared Pointers use what we call reference counts to keep track of the number of 
	// pointers to an object.Everytime a new pointer points to the object, the reference 
	// count is incremented.

	shared_ptr<IMedia> pSong1 = make_shared<Song>(L"Nothing on You", L"Bruno Mars");
	cout << pSong1.use_count() << endl;
	shared_ptr<Song> pSong2 = make_shared<Song>(L"Born in the USA", L"Bruce Springsteen");
	cout << pSong2.use_count() << endl;

	// Use pSong1...note the scope
	if (1) {
		shared_ptr<IMedia> pSong12 = pSong1;
		cout << pSong1.use_count() << endl;
	}
	cout << pSong1.use_count() << endl;
	pSong1->playMedia();

	// Use pSong2...note the scope
	if (1) {
		shared_ptr<Song> pSong22 = pSong2;
		cout << pSong2.use_count() << endl;
	}
	cout << pSong2.use_count() << endl;
	pSong2->printSong();
	pSong2->playMedia();
}

void UseSmartUniquePointer()
{
	// The second main type of Smart Pointer, is the Unique Pointer.
	// It’s a type of pointer that is used to manage the lifetime of an object.
	// Unique Pointers are unique in that there can only be one Unique Pointer to an object.
	// If you try to create a second Unique Pointer to the same object, you will get a compile error.
	// Unique Pointers are useful when you want to ensure that an object is deleted when it is no longer needed.

	unique_ptr<IMedia> pSong1 = make_unique<Song>(L"Nothing on You", L"Bruno Mars");
	unique_ptr<Song> pSong2 = make_unique<Song>(L"Born in the USA", L"Bruce Springsteen");

	// Use pSong1...
	unique_ptr<IMedia> p2 = move(pSong1);
	p2->playMedia();
	// pSong1->playMedia();; // Throws an error because pSong1 is a unique pointer and it has been moved to p2

	// Use pSong2...
	pSong2->printSong();
	pSong2->playMedia();

	// Note: There is one exception to the “only one pointer at a time”. 
	// We can copy or assign a unique_ptr that is about to be destroyed. 
	// For example, when we return a unique pointer from a function. 
	// The compiler will know that the object is about to be destroyed, and performs a special copy.
}

void UseSmartWeakPointer()
{
	// The third main type of Smart Pointer, is the Weak Pointer.
	// The Weak Pointer class is a sort of extension, or companion of the Shared Pointer.
	// It does not manage the life time of the object that it points to, unlike the other two smart pointers.
	// It instead, points to an object that is managed by a shared pointer, but unlike a regular shared pointer, 
	// it does not increase the reference count.
	// This is why it’s called a “weak” pointer.
	// You can’t directly use a Weak Pointer, and need to use the lock() function.
	// This returns a shared pointer to the object it was pointing to, if the object still exists.
	// If the reference count has dropped to zero however, and the object is deleted, it will return NULL.
	// It’s a type of pointer that is used to break circular references between shared pointers.
	// Weak Pointers are used to avoid memory leaks.
	// Weak Pointers are used in conjunction with Shared Pointers.
	// Weak Pointers do not affect the reference count of the object.
	// Weak Pointers are used to check if the object is still alive.
	// Weak Pointers are used to access the object if it is still alive.
	// Weak Pointers are used to convert to a Shared Pointer.
	// Weak Pointers are used to convert to a Shared Pointer only if the object is still alive.
	// Weak Pointers are used to convert to a Shared Pointer only if the object is still alive, otherwise it returns a nullptr.

	shared_ptr<IMedia> pSong1 = make_shared<Song>(L"Nothing on You", L"Bruno Mars");
	cout << pSong1.use_count() << endl;

	// Use pSong1...
	pSong1->playMedia();

	weak_ptr<IMedia> pWeakSong1 = pSong1;
	cout << pSong1.use_count() << endl;
	// Another way
	weak_ptr<IMedia> weakp(pSong1);
	cout << pSong1.use_count() << endl;

	// Use pWeakSong1...
	if (shared_ptr<IMedia> pSong1Shared = pWeakSong1.lock()) {
		pSong1Shared->playMedia();
	}
	else {
		cout << "The object is no longer alive." << endl;
	}

	// Other ways
	weak_ptr<Song> wp;

	if (1) {
		shared_ptr<Song> sp = make_shared<Song>(L"Born in the USA", L"Bruce Springsteen");
		wp = sp;

		auto p = wp.lock();
		if (p) {
			cout << "Connection Intact" << endl;
		}
		else {
			cout << "Pointing to Null" << endl;
		}
	}

	auto p = wp.lock();
	if (p) {
		cout << "Connection Intact" << endl;
	}
	else {
		cout << "Pointing to Null" << endl;
	}
}