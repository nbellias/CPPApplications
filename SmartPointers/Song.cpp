#include "Song.h"
#include <iostream>


Song::Song(wstring title, wstring artist)
{
	m_title = title;
	m_artist = artist;
}

Song::~Song()
{
}

wstring Song::GetTitle() const
{
    return wstring();
}

wstring Song::GetArtist() const
{
    return wstring();
}

void Song::printSong() const
{
	wcout << L"Title: " << m_title << L" Artist: " << m_artist << endl;
}

void Song::playMedia() const
{
	// Play the song...
	printSong();
	wcout << L"Playing song..." << endl;
}
