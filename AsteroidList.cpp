#include <galaxy-explorer/AsteroidList.hpp>

//AsteroidListItem constructor 

AsteroidListItem::AsteroidListItem() {
    this -> next = nullptr;
    this -> data = nullptr;
}
//AsteroidListItem constructor given an asteroid

AsteroidListItem::AsteroidListItem(Asteroid a) {
    this -> next = nullptr;
    this -> data = new Asteroid(a); //Calling default copy constructor
}

AsteroidListItem::~AsteroidListItem() {
    this -> next = nullptr;
    delete this -> data;
    this -> data = nullptr;
    
}

//Constructor for AsteroidList

AsteroidList::AsteroidList() {
    head.setNext(nullptr);
}

//Copy constructor for the class AsteroidList

AsteroidList::AsteroidList(const AsteroidList& src) {

    const AsteroidListItem* tempSrc = src.begin(); //Retrieving first asteroid
    AsteroidListItem* tempHead = &head; //Second item and beyond
    bool first = true;

    while (tempSrc != nullptr) {
        AsteroidListItem* listData = new AsteroidListItem(tempSrc -> getData());
        if (first) {
            head.setNext(listData); //Setting the the next element of head on the first iteration
            first = false;
        } else
            tempHead -> setNext(listData);

        tempHead = tempHead -> getNext(); //Lagging one behind to set data 
        tempSrc = tempSrc -> getNext(); //Iterator  
    }


}

//Destructor, simply clear the list
AsteroidList::~AsteroidList() {
    clear(); //Calling clear to delete
}

//Add an asteroid at the beginning of this list

void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* temp = new AsteroidListItem(e); //Making a copy
    temp -> setNext(head.getNext()); //temp now points to previous first element
    head.setNext(temp);
}

//Return a reference to the first asteroid

Asteroid& AsteroidList::front() {
    if (beforeBegin() -> hasNext())
        return begin() -> getData();

    return *(Asteroid*) nullptr;
}

//Same as above except with the const modifier

const Asteroid& AsteroidList::front() const {
    if (beforeBegin() -> hasNext())
        return begin() -> getData();

    return *(const Asteroid*) nullptr;
}

//Check if the list is empty

bool AsteroidList::isEmpty() const {
    return !head.hasNext();
}

//Count the number of entries (Asteroids)in the list 

int AsteroidList::size() const {

    if (isEmpty())
        return 0;

    int count = 0;
    const AsteroidListItem* temp = begin(); //Iterator, starting at first asteroid

    while (temp != nullptr) {
        count++;
        temp = temp -> getNext();
    }

    return count;
}

//Return the head of the list

AsteroidListItem* AsteroidList::beforeBegin() {
    return &head; //Before begin is the head of list 
}

//Same as above except with the const modifier

const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;
}

//Return the pointer to the AstroidList containing the first asteroid.

AsteroidListItem* AsteroidList::begin() {
    return head.getNext(); //First Asteroid is the item directly after next
}

//Same as above except with the const modifier

const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}
//Return the pointer to the AstroidList containing the last asteroid.

AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* temp = this -> begin();
    if (temp == nullptr) //Empty list
        return this -> beforeBegin();

    while (temp -> hasNext()) {
        temp = temp -> getNext(); //Iterate till end
    }

    return temp;
}
//Same as above except with the const modifier

const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem* temp = this -> begin();
    if (temp == nullptr)
        return this -> beforeBegin();

    while (temp -> hasNext()) {
        temp = temp -> getNext();
    }
    return temp;
}

//Return the pointer to the address immediately after the last asteroid

AsteroidListItem* AsteroidList::end() {
    return nullptr; //Nothing after last asteroid
}

//Same as above except with the const modifier

const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

//Add a single asteroid to this list, in the position immediately after `prev`
//Returns the inserted item

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* addedAsteroid = new AsteroidListItem(e);
    addedAsteroid -> setNext(prev -> getNext()); //Setting next for the added asteroid
    prev -> setNext(addedAsteroid); //Changing next for previous asteroid
    return addedAsteroid;

}


// Add independent copies of the entities in `others` to this list, placed immediately after `insertion_point`,
//in the same order as `others`.

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {

    if (others.isEmpty()) //Empty list
        return prev;

    const AsteroidListItem* temp = others.begin();
    while (temp != nullptr) {
        AsteroidListItem* addedAsteroid = new AsteroidListItem(temp -> getData());
        addedAsteroid -> setNext(prev -> getNext()); // Changing prev to point to asteroid being added
        prev -> setNext(addedAsteroid);

        prev = prev -> getNext(); //Lagging one iteration behind to set the next element
        temp = temp -> getNext();
    }

    return prev;

}

//Given a position in this list, delete the following asteroid.
//Returns the asteroid following the deleted asteroid.

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    
    if(!prev -> hasNext()) //Checking for empty list
        return nullptr;
    
    AsteroidListItem* temp = prev -> getNext();
    
    prev -> setNext(prev -> getNext() -> getNext()); //Prev points to item after deleted
    delete temp;
    return prev -> getNext();
}

//Make this list empty, free all nodes.

void AsteroidList::clear() {
    while(!isEmpty()){ //Iterate through entire list
        eraseAfter(&head); //Calling erase to delete
    }
}

//Makes this list an independent copy of `src`. deep copy

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if(this == &src)
        return *(this);
    
    this -> clear();
    this -> insertAfter(&head, src); //Insert entire list into object calling the operator
    
    return *(this);
}
