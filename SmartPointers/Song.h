#pragma once
#include <string>
#include "IMedia.h"

using namespace std;

#ifndef SONG_H
#define SONG_H

class Song : public IMedia {
public:
	Song(wstring title, wstring artist);
	~Song() override;
	wstring GetTitle() const;
	wstring GetArtist() const;

	void printSong() const;
	void playMedia() const override;

private:
	wstring m_title;
	wstring m_artist;
};

#endif // !SONG_H
