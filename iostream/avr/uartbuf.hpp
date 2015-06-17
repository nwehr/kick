#ifndef _kick_iostream_uartbuf_h
#define _kick_iostream_uartbuf_h

//
// Copyright 2012-2015 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <string.h>
#include <stdint.h>

#include <avr/io.h>

// Kick
#include "../streambuf.hpp"

#ifndef FOSC
	#define	FOSC 16000000UL
#endif

#ifndef KICK_POLYMORPHIC_UARTBUF
	#define KICK_POLYMORPHIC_UARTBUF KICK_POLYMORPHIC_STREAMBUF
#endif

#ifndef KICK_UART_BAUD
	#define KICK_UART_BAUD 19200
#endif

#ifndef KICK_UART_DATABITS
	#define KICK_UART_DATABITS 3
#endif

#ifndef KICK_UART_BUFFERSIZE
	#define KICK_UART_BUFFERSIZE 8
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_uartbuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	template <typename CharT>
	class basic_uartbuf : public basic_streambuf<CharT> {
		basic_uartbuf(const basic_uartbuf&);
		
	public:
		basic_uartbuf();
		
#ifdef KICK_POLYMORPHIC_UARTBUF
		virtual
#endif
		~basic_uartbuf();
		
	protected:
		inline void tx_start() {
			UCSR0B |= _BV(TXEN0);
		}
		
		inline void tx_stop() {
			UCSR0B &= ~_BV(TXEN0);
		}
		
		inline void rx_start() {
			UCSR0B |= _BV(RXEN0);
		}
		
		inline void rx_stop() {
			UCSR0B &= ~_BV(RXEN0);
		}
		
		inline void enable_tx_interupt() {
			UCSR0B |= _BV(TXCIE0);
		}
		
		inline void disable_tx_interupt() {
			UCSR0B &= ~_BV(TXCIE0);
		}
		
		inline void enable_rx_interupt() {
			UCSR0B |= _BV(RXCIE0);
		}
		
		inline void disable_rx_interupt() {
			UCSR0B &= ~_BV(RXCIE0);
		}
		
#ifdef KICK_POLYMORPHIC_UARTBUF
		virtual
#endif
		int sync() {
			for( pos_type spos = this->_opos_beg; spos < this->_opos; ++spos ) {
				// Stay here until data buffer is empty
				while (!(UCSR0A & _BV(UDRE0))) {}
				
				UDR0 = this->_buf[spos];
			}
			
			this->_opos = this->_opos_beg;
			
			return basic_streambuf<CharT>::sync_ok;
		}
		
		unsigned long _baud;
		
		unsigned int _databits;
		unsigned int _ubbr;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// uartbuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_uartbuf<char> uartbuf;
	
}

///////////////////////////////////////////////////////////////////////////////
// basic_uartbuf : basic_streambuf
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
kick::basic_uartbuf<CharT>::basic_uartbuf()
: kick::basic_streambuf<CharT>::basic_streambuf()
, _baud		(KICK_UART_BAUD)
, _databits	(KICK_UART_DATABITS)
, _ubbr		((FOSC/16)/_baud - 1)
{
	this->setbuf(new char[KICK_UART_BUFFERSIZE](), KICK_UART_BUFFERSIZE);
	
	// Not necessary; initialize anyway
	DDRD |= (1 << PD1);
	DDRD &= ~(1 << PD0);
	
	// Set baud rate; lower byte and top nibble
	UBRR0H = ((_ubbr) & 0xF00);
	UBRR0L = (uint8_t) ((_ubbr) & 0xFF);
	
	tx_start();
	rx_start();
	
	// Set frame format = 8-N-1
	UCSR0C = (_databits << UCSZ00);
}

template <typename CharT>
kick::basic_uartbuf<CharT>::basic_uartbuf(const kick::basic_uartbuf<CharT>& buf){}

template <typename CharT>
kick::basic_uartbuf<CharT>::~basic_uartbuf(){
	delete[] this->_buf;
}





#endif