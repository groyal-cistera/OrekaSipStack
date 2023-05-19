/*
 * Oreka -- A media capture and retrieval platform
 *
 * Copyright (C) 2005, orecx LLC
 *
 * http://www.orecx.com
 *
 */
#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
//#include "winsock2.h"
#endif
#include "SipHeaders.h"
#include "Utils.h"
#include "MemUtils.h"


//==========================================================
SipInviteInfo::SipInviteInfo() : m_telephoneEventPayloadType(0)
{
	m_fromRtpIp.s_addr = 0;
	m_validated = false;
	m_attrSendonly = false;
	m_SipGroupPickUpPatternDetected = false;
	memset(m_orekaRtpPayloadTypeMap, 0, sizeof(m_orekaRtpPayloadTypeMap));
}

void SipInviteInfo::ToString(CStdString& string)
{
	char fromRtpIp[16];
	inet_ntopV4(AF_INET, (void*)&m_fromRtpIp, fromRtpIp, sizeof(fromRtpIp));

	char senderIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));

	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	CStdString senderMac, receiverMac;

	MemMacToHumanReadable((unsigned char*)m_senderMac, senderMac);
	MemMacToHumanReadable((unsigned char*)m_receiverMac, receiverMac);

	string.Format("{\"method\":\"RTP_INVITE\", \"sender\":\"%s\", \"from\":\"%s@%s\",\"full_from\":\"%s\",\"rtpIp\":\"%s\", \"rtpPort\":\"%s\", \"to\":\"%s@%s\", \"rcvr\":\"%s\", \"callid\":\"%s\", \"sendermac\":\"%s\", \"receivermac\":\"%s\", \"fromname\":\"%s\", \"toname\":\"%s\", \"useragent\":\"%s\"}", senderIp, m_from, m_fromDomain, m_fullfrom, fromRtpIp, m_fromRtpPort, m_to, m_toDomain, receiverIp, m_callId, senderMac, receiverMac, m_fromName, m_toName, m_userAgent);
}

//==========================================================
Sip302MovedTemporarilyInfo::Sip302MovedTemporarilyInfo()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
}

void Sip302MovedTemporarilyInfo::ToString(CStdString& string)
{
	char senderIp[16];
	char receiverIp[16];

	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("sender:%s rcvr:%s from:%s@%s to:%s@%s contact:%s@%s fromname:%s toname:%s contactname:%s callid:%s", senderIp, receiverIp, m_from, m_fromDomain, m_to, m_toDomain, m_contact, m_contactDomain, m_fromName, m_toName, m_contactName, m_callId);
}

//==========================================================
SipFailureMessageInfo::SipFailureMessageInfo()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
	memset(m_senderMac, 0, sizeof(m_senderMac));
	memset(m_receiverMac, 0, sizeof(m_receiverMac));
}

void SipFailureMessageInfo::ToString(CStdString& string)
{
	char senderIp[16], receiverIp[16];
	CStdString senderMac, receiverMac;

	MemMacToHumanReadable((unsigned char*)m_senderMac, senderMac);
	MemMacToHumanReadable((unsigned char*)m_receiverMac, receiverMac);
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("sender:%s rcvr:%s smac:%s rmac:%s callid:%s errorcode:%s reason:\"%s\"", senderIp, receiverIp, senderMac, receiverMac, m_callId, m_errorCode, m_errorString);
}

void SipFailureMessageInfo::ToString(CStdString& string, SipInviteInfoRef inviteInfo)
{
	char senderIp[16], receiverIp[16];
	CStdString senderMac, receiverMac;

	//MemMacToHumanReadable((unsigned char*)m_senderMac, senderMac);
	//MemMacToHumanReadable((unsigned char*)m_receiverMac, receiverMac);
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("sender:%s from:%s to:%s rcvr:%s callid:%s errorcode:%s reason:\"%s\"", senderIp, inviteInfo->m_from, inviteInfo->m_to, receiverIp, inviteInfo->m_callId, m_errorCode, m_errorString);
}

//============================
Sip200OkInfo::Sip200OkInfo()
{
	m_mediaIp.s_addr = 0;
	m_hasSdp = false;
}

void Sip200OkInfo::ToString(CStdString& string)
{
	char mediaIp[16];
	inet_ntopV4(AF_INET, (void*)&m_mediaIp, mediaIp, sizeof(mediaIp));

	char senderIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));

	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	CStdString senderMac, receiverMac;

	MemMacToHumanReadable((unsigned char*)m_from_mac, senderMac);
	MemMacToHumanReadable((unsigned char*)m_to_mac, receiverMac);

	if(m_mediaPort.size())
	{
		string.Format("{\"method\":\"RTP_INVITE_OK\", \"sender\":\"%s\", \"from\":\"%s\",\"full_from\":\"%s\",\"rtpIp\":\"%s\",\"rtpPort\":\"%s\", \"to\":\"%s\", \"rcvr\":\"%s\", \"callid\":\"%s\", \"codec\":\"%s\", \"useragent\":\"%s\", \"senderMac\":\"%s\", \"receiverMac\":\"%s\"}", senderIp, m_from, m_fullfrom, mediaIp, m_mediaPort, m_to, receiverIp, m_callId, m_codec, m_userAgent, senderMac, receiverMac);
	}
	else
	{
		string.Format("{\"method\":\"200OK\", \"sender\":\"%s\", \"from\":\"%s\",\"full_from\":\"%s\",\"to\":\"%s\", \"rcvr\":\"%s\", \"callid\":\"%s\", \"useragent\":\"%s\", \"senderMac\":\"%s\", \"receiverMac\":\"%s\"}", senderIp, m_from, m_fullfrom, m_to, receiverIp, m_callId, m_userAgent, senderMac, receiverMac);
	}
}


//================================================
SipSessionProgressInfo::SipSessionProgressInfo()
{
	m_mediaIp.s_addr = 0;
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
}

void SipSessionProgressInfo::ToString(CStdString& string)
{
	char mediaIp[16];
	inet_ntopV4(AF_INET, (void*)&m_mediaIp, mediaIp, sizeof(mediaIp));

	char senderIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));

	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("sender:%s from:%s RTP:%s,%s to:%s rcvr:%s callid:%s", senderIp, m_from, mediaIp, m_mediaPort, m_to, receiverIp, m_callId);
}

//================================================
SipByeInfo::SipByeInfo()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
}

void SipByeInfo::ToString(CStdString& string)
{
	char senderIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));

	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("{\"method\":\"BYE\", \"sender\":\"%s\", \"rcvr\":\"%s\", \"callid\":\"%s\", \"from\":\"%s\", \"to\":\"%s\", \"fromName\":\"%s\", \"toName\":\"%s\", \"callid\":\"%s\"}", senderIp, receiverIp, m_callId, m_from, m_to, m_fromName, m_toName, m_callId);
}

//================================================
SipNotifyInfo::SipNotifyInfo() : m_onHoldMarker(false), m_offHoldMarker(false)
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
}
//================================================
SipInfo::SipInfo()
{
	m_onDemand = false;
	m_onDemandOff = false;
}
//==================================================
SipRefer::SipRefer()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
	m_sipMethod = "REFER";
}

void SipRefer::ToString(CStdString& string)
{
	char senderIp[16];
	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("{\"method\":\"%s\", \"sender\":\"%s\", \"rcvr\":\"%s\", \"from\":\"%s@%s\", \"to\":\"%s@%s\", \"fromname\":\"%s\", \"toname\":\"%s\", \"referto\":\"%s\", \"referredby\":\"%s\", \"referredParty\":\"%s\", \"callid\":\"%s\"}", m_sipMethod, senderIp, receiverIp, m_from, m_fromDomain, m_to, m_toDomain, m_fromName, m_toName, m_referToParty, m_referredByParty, m_referredParty, m_callId);
}
//==================================================
SipSubscribeInfo::SipSubscribeInfo()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
	m_sipMethod = "SUBSCRIBE";

}
void SipSubscribeInfo::ToString(CStdString& string)
{
	char senderIp[16];
	char receiverIp[16];
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	//string.Format("{\"method\":\"SUBSCRIBE\", \"sender\":\"%s\", \"rcvr\":\"%s\", \"from\":\"%s@%s\", \"to\":\"%s@%s\", \"fromname\":\"%s\", \"toname\":\"%s\" }", senderIp, receiverIp, m_from, m_fromDomain, m_to, m_toDomain, m_fromName, m_toName);
}
//==================================================
SipRegisterInfo::SipRegisterInfo()
{
	m_senderIp.s_addr = 0;
	m_receiverIp.s_addr = 0;
	m_sipMethod = "REGISTER";

}
void SipRegisterInfo::ToString(CStdString& string)
{
	char senderIp[16];
	char receiverIp[16];
	CStdString senderMac, receiverMac;

	MemMacToHumanReadable((unsigned char*)m_senderMac, senderMac);
	MemMacToHumanReadable((unsigned char*)m_receiverMac, receiverMac);
	inet_ntopV4(AF_INET, (void*)&m_senderIp, senderIp, sizeof(senderIp));
	inet_ntopV4(AF_INET, (void*)&m_receiverIp, receiverIp, sizeof(receiverIp));

	string.Format("{\"method\":\"%s\", \"sender\":\"%s\", \"rcvr\":\"%s\", \"sendermac\":\"%s\", \"receivermac\":\"%s\", \"from\":\"%s@%s\", \"to\":\"%s@%s\", \"fromname\":\"%s\", \"toname\":\"%s\", \"useragent\":\"%s\", \"requesturi\":\"%s\"}", m_sipMethod , senderIp, receiverIp, senderMac, receiverMac, m_from, m_fromDomain, m_to, m_toDomain, m_fromName, m_toName, m_userAgent, m_request_uri );
}


