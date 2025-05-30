// Copyright 2019 The gRPC Authors

package http2interop

import (
	"fmt"
	"time"
)

func testSmallMaxFrameSize(ctx *HTTP2InteropCtx) error {
	conn, err := connect(ctx)
	if err != nil {
		return err
	}
	defer conn.Close()
	conn.SetDeadline(time.Now().Add(defaultTimeout))

	sf := &SettingsFrame{
		Params: []SettingsParameter{{
			Identifier: SettingsMaxFrameSize,
			Value:      1<<14 - 1,
		}},
	}

	if err := http2Connect(conn, sf); err != nil {
		return err
	}

	if _, err := expectGoAwaySoon(conn); err != nil {
		return err
	}

	return nil
}

func testAllSettingsFramesAcked(ctx *HTTP2InteropCtx) error {
	conn, err := connect(ctx)
	if err != nil {
		return err
	}
	defer conn.Close()
	conn.SetDeadline(time.Now().Add(defaultTimeout))

	sf := &SettingsFrame{}
	if err := http2Connect(conn, sf); err != nil {
		return err
	}

	for i := 0; i < 10; i++ {
		if err := streamFrame(conn, sf); err != nil {
			return err
		}
	}

	var settingsFramesReceived = 0

	for settingsFramesReceived < 12 {
		f, err := parseFrame(conn)
		if err != nil {
			return err
		}

		if f, ok := f.(*SettingsFrame); ok {
			settingsFramesReceived += 1
			if settingsFramesReceived == 1 {
				if f.Header.Flags&SETTINGS_FLAG_ACK > 0 {
					return fmt.Errorf("settings frame should not have used ack: %v", f)
				}
				continue
			}

			if f.Header.Flags&SETTINGS_FLAG_ACK == 0 {
				return fmt.Errorf("settings frame should have used ack: %v", f)
			}
			if len(f.Params) != 0 {
				return fmt.Errorf("settings ack cannot have params: %v", f)
			}
		}
	}

	return nil
}
