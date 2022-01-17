/*
 * Copyright 2018, 2019, 2020, 2021 Dooboolab.
 *
 * This file is part of Flutter-Sound.
 *
 * Flutter-Sound is free software: you can redistribute it and/or modify
 * it under the terms of the Mozilla Public License version 2 (MPL2.0),
 * as published by the Mozilla organization.
 *
 * Flutter-Sound is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * MPL General Public License for more details.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */


#ifndef FlautoPlayer_h
#define FlautoPlayer_h



#import "Flauto.h"
#import <AVFoundation/AVFoundation.h>
#import "FlautoPlayerEngine.h"
#import "FlautoSession.h"
#import "FlautoTrack.h"



@protocol FlautoPlayerCallback <NSObject>

- (void)openPlayerCompleted: (bool)success;
- (void)closePlayerCompleted: (bool)success;
- (void)startPlayerCompleted: (bool)success duration: (long)duration;
- (void)pausePlayerCompleted: (bool)success;
- (void)resumePlayerCompleted: (bool)success;
- (void)stopPlayerCompleted: (bool)success;

- (void)needSomeFood: (int) ln;
- (void)updateProgressPosition: (long)position duration: (long)duration;
- (void)audioPlayerDidFinishPlaying: (BOOL)flag;
- (void)pause;
- (void)resume;
- (void)skipForward;
- (void)skipBackward;
- (void)log: (t_LOG_LEVEL)level msg: (NSString*)msg;
@end


@interface FlautoPlayer  : FlautoSession <AVAudioPlayerDelegate>
{
        NSObject<FlautoPlayerEngineInterface>* m_playerEngine;
        NSObject<FlautoPlayerCallback>* m_callBack;
}

- (FlautoPlayer*)init: (NSObject<FlautoPlayerCallback>*) callback;
           
- (t_PLAYER_STATE)getPlayerState;
- (bool)isDecoderSupported: (t_CODEC)codec ;

- (bool)initializeFlautoPlayerFocus:
                (t_AUDIO_FOCUS)focus
                category: (t_SESSION_CATEGORY)category
                mode: (t_SESSION_MODE)mode
                audioFlags: (int)audioFlags
                audioDevice: (t_AUDIO_DEVICE)audioDevice;
                
- (void)releaseFlautoPlayer;

- (bool)startPlayerCodec: (t_CODEC)codec
        fromURI: (NSString*)path
        fromDataBuffer: (NSData*)dataBuffer
        channels: (int)numChannels
        sampleRate: (long)sampleRate
        ;
- (bool)startPlayerFromMicSampleRate: (long)sampleRate nbChannels: (int)nbChannels;
- (bool)startPlayerFromTrack: (FlautoTrack*)track canPause: (bool)canPause canSkipForward: (bool)canSkipForward canSkipBackward: (bool)canSkipBackward
        progress: (NSNumber*)progress duration: (NSNumber*)duration removeUIWhenStopped: (bool)removeUIWhenStopped defaultPauseResume: (bool)defaultPauseResume;

- (void)stopPlayer;
- (bool)pausePlayer;
- (bool)resumePlayer;
- (void)seekToPlayer: (long)time;
- (void)setSubscriptionDuration: (long)call ;
- (void)setVolume: (double)volume fadeDuration: (NSTimeInterval) fadeDuration;
- (void)setSpeed: (double)speed ;
- (bool)setCategory: (NSString*)categ mode:(NSString*)mode options:(int)options ;
- (bool)setActive:(BOOL)enabled ;
- (void)setUIProgressBar: (NSNumber*)pos duration: (NSNumber*)duration;
- (NSDictionary*)getProgress ;
- (int)feed: (NSData*)data;
- (void)needSomeFood: (int) ln;
- (t_PLAYER_STATE)getStatus;
- (void)startTimer;
- (void)stopTimer;
- (long)getPosition;
- (long)getDuration;
- (void)nowPlaying: (FlautoTrack*)track canPause: (bool)canPause canSkipForward: (bool)canSkipForward canSkipBackward: (bool)canSkipBackward
                defaultPauseResume: (bool)defaultPauseResume progress: (NSNumber*)progress duration: (NSNumber*)duration;
- (void)logDebug: (NSString*)msg;




@end

#endif // FlautoPlayer_h

