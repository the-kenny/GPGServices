//
//  GPGServices.h
//  GPGServices
//
//  Created by Robert Goldsmith on 24/06/2006.
//  Copyright 2006 far-blue.co.uk. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>
#import <Growl/Growl.h>

typedef BOOL(^KeyValidatorT)(GPGKey* key);

typedef enum {
    SignService, 
    EncryptService, 
    DecryptService, 
    VerifyService, 
    MyKeyService, 
    MyFingerprintService, 
    ImportKeyService,
} ServiceModeEnum;

@interface GPGServices : NSObject <GrowlApplicationBridgeDelegate>
{
	IBOutlet NSWindow *recipientWindow;
	
	IBOutlet NSWindow *passphraseWindow;
	IBOutlet NSSecureTextField *passphraseText;
	
	NSTimer *currentTerminateTimer;
}

-(void)applicationDidFinishLaunching:(NSNotification *)aNotification;


#pragma mark -
#pragma mark GPG-Helper

-(void)importKey:(NSString *)inputString;
+ (NSSet*)myPrivateKeys;
+ (GPGKey*)myPrivateKey;

#pragma mark -
#pragma mark Validators

+ (KeyValidatorT)canSignValidator;
+ (KeyValidatorT)canEncryptValidator;
+ (KeyValidatorT)isActiveValidator;

#pragma mark -
#pragma mark Text Stuff

-(NSString *)myFingerprint;
-(NSString *)myKey;
-(NSString *)signTextString:(NSString *)inputString;
-(NSString *)encryptTextString:(NSString *)inputString;
-(NSString *)decryptTextString:(NSString *)inputString;
-(void)verifyTextString:(NSString *)inputString;


#pragma mark -
#pragma mark File Stuff

- (void)encryptFiles:(NSArray*)files;


#pragma mark -
#pragma mark Service handling routines

-(void)dealWithPasteboard:(NSPasteboard *)pboard
                 userData:(NSString *)userData 
                     mode:(ServiceModeEnum)mode
                    error:(NSString **)error;
-(void)exitServiceRequest;
-(void)sign:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)encrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)decrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)verify:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)myKey:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)myFingerprint:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)importKey:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void)encryptFile:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;


#pragma mark -
#pragma mark UI Helpher

-(void)displayMessageWindowWithTitleText:(NSString *)title bodyText:(NSString *)body;
-(NSString *)context:(GPGContext *)context passphraseForKey:(GPGKey *)key again:(BOOL)again;
-(IBAction)closeModalWindow:(id)sender;
- (NSURL*)getFilenameForSavingWithSuggestedPath:(NSString*)path
                         withSuggestedExtension:(NSString*)ext;

-(void)cancelTerminateTimer;
-(void)goneIn60Seconds;
-(void)selfQuit:(NSTimer *)timer;

@end
