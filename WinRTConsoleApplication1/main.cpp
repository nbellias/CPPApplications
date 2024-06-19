﻿#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;


int main()
{
    init_apartment();
    /*
    Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());
    */
    
    Uri rssFeedUri{ L"https://blogs.windows.com/feed" };
    SyndicationClient syndicationClient;
    syndicationClient.SetRequestHeader(L"User-Agent", L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)");
    SyndicationFeed syndicationFeed = syndicationClient.RetrieveFeedAsync(rssFeedUri).get();
    for (const SyndicationItem syndicationItem : syndicationFeed.Items())
    {
        winrt::hstring titleAsHstring = syndicationItem.Title().Text();

        // A workaround to remove the trademark symbol from the title string, because it causes issues in this case.
        std::wstring titleAsStdWstring{ titleAsHstring.c_str() };
        titleAsStdWstring.erase(remove(titleAsStdWstring.begin(), titleAsStdWstring.end(), L'™'), titleAsStdWstring.end());
        titleAsHstring = titleAsStdWstring;

        std::wcout << titleAsHstring.c_str() << std::endl;
    }
}
