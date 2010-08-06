#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>
#include "quicklooknfo.h"

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
    if (QLPreviewRequestIsCancelled(preview))
        return noErr;
    
  	CFDataRef data = createHTMLPreview( url );

    if (!data || QLPreviewRequestIsCancelled(preview)) {
		return noErr;
    }
	
	CFStringRef keys[1];
	CFStringRef values[1];
	values [0] = CFStringCreateWithCString(NULL, "UTF-8", kCFStringEncodingUTF8);
	keys[0] = kQLPreviewPropertyTextEncodingNameKey;
    CFDictionaryRef properties = CFDictionaryCreate(NULL, (void*) keys, (void*) values, 1, NULL, NULL);
    QLPreviewRequestSetDataRepresentation(preview, (CFDataRef)data, 
                                          kUTTypeHTML, 
                                          properties);

	CFRelease(data);
	CFRelease(values[0]);
	CFRelease(properties);

    return noErr;
}

void CancelPreviewGeneration(void* thisInterface, QLPreviewRequestRef preview)
{
	
}
