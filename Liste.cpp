//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXIV
//////////////////////////////////////////////////////////////////////////////

#include "Liste.h"

/**
 * @brief Standardkonstruktor, der eine leere Liste erstellt
 */
Liste::Liste(): front(nullptr), back(nullptr)
{
}

/**
 * @brief Destruktor, gibt den gesamten allokierten Speicher frei
 */
Liste::~Liste()
{
    ListenElement* cursor = front;

    while (cursor != nullptr)
    {
        ListenElement* temp = cursor->getNext();
        delete cursor;
        cursor = temp;
    }

    front = nullptr;
    back = nullptr;
}

/**
 * @brief Hinzufuegen eines neuen Listenelements am Ende der Liste.
 *
 * @param pData Zeiger auf ein Objekt der Klasse Student
 * @return void
 */
void Liste::pushBack(Student pData)
{
    ListenElement* neuesElement = new ListenElement(pData, nullptr, back);

    if (front == nullptr)                                       // Liste leer?
    {
        front = neuesElement;
        back = neuesElement;
    }
    else
    {
        back->setNext(neuesElement);
        back = neuesElement;
    }
}

/**
 * @brief Hinzufuegen eines neuen Listenelements am Anfang der Liste.
 *
 * @param pData Objekt der Klasse Student
 * @return void
 */
void Liste::pushFront(Student pData)
{
    ListenElement* neuesElement = new ListenElement(pData, front, nullptr);

    if (front == nullptr)                                       // Liste leer?
    {
        front = neuesElement;
        back = neuesElement;
    }
    else
    {
        front->setPrev(neuesElement);
        front = neuesElement;
    }
}

/**
 * @brief Entfernen eines Listenelements am Anfang der Liste.
 *
 * @return void
 */
void Liste::popFront()
{
    if (front != nullptr)                                      // Liste nicht leer?
    {
        ListenElement* cursor = front;

        if (front == back)                                    // Liste enthält nur ein Listenelement
        {
            delete front;                                     // Listenelement löschen
            front = nullptr;
            back = nullptr;
        }
        else
        {
            front = front->getNext();
            front->setPrev(nullptr);                          // Prev-Zeiger des neuen ersten Elements auf nullptr setzen
            delete cursor;
        }
    }
}

/**
 * @brief Pruefen, ob die Liste leer ist
 *
 * @return wenn leer true, sonst false
 */
bool Liste::empty()
{
    if(front == nullptr)
    {
        return true;
    }
    return false;
}

/**
 * @brief Gibt die Daten des ersten Listenelements in der Liste zurueck
 *
 * @return Student-Objekt des ersten Elements
 */
Student Liste::dataFront()
{
    if (front != nullptr)
    {
        return front->getData();
    }
    else
    {
        // Rückgabe eines leeren Studenten-Objekts, wenn die Liste leer ist
        return Student();
    }
}

/**
 * @brief Ausgabe der Liste vom ersten bis zum letzten Element.
 *
 * @return void
 */
void Liste::ausgabeVorwaerts() const
{
    ListenElement* cursor = front;

    while (cursor != nullptr)
    {
        cursor->getData().ausgabe();
        cursor = cursor->getNext();
    }
}

/**
 * @brief Ausgabe der Liste vom letzten bis zum ersten Element.
 *
 * @return void
 */
void Liste::ausgabeRueckwaerts() const
{
    ListenElement* cursor = back;

    while (cursor != nullptr)
    {
        cursor->getData().ausgabe();
        cursor = cursor->getPrev();
    }
}

/**
 * @brief Löscht das Element mit der angegebenen Matrikelnummer.
 *
 * @param matNr Matrikelnummer des zu löschenden Elements
 * @return true, wenn das Element gefunden und gelöscht wurde, sonst false
 */
bool Liste::deleteNode(unsigned int matNr)
{
    ListenElement* cursor = front;

    // Liste durchsuchen, um das Element mit der angegebenen Matrikelnummer zu finden
    while (cursor != nullptr)
    {
        if (cursor->getData().getMatNr() == matNr)
        {
            // Element gefunden - nun löschen
            if (cursor == front && cursor == back)   // Einziges Element in der Liste
            {
                front = nullptr;
                back = nullptr;
            }
            else if (cursor == front)                // Erstes Element der Liste
            {
                front = cursor->getNext();
                front->setPrev(nullptr);
            }
            else if (cursor == back)                 // Letztes Element der Liste
            {
                back = cursor->getPrev();
                back->setNext(nullptr);
            }
            else                                    // Element in der Mitte der Liste
            {
                cursor->getPrev()->setNext(cursor->getNext());
                cursor->getNext()->setPrev(cursor->getPrev());
            }

            delete cursor;
            return true;
        }

        cursor = cursor->getNext();
    }

    // Element nicht gefunden
    return false;
}
