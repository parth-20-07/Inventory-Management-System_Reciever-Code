#include <pgmspace.h>

#define SECRET

const char ssid[] = "project105";
const char pass[] = "project105";

#define THINGNAME "123456789"

//int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
//#define USE_SUMMER_TIME_DST  //uncomment to use DST

const char MQTT_HOST[] = "auu7lvgox59ol-ats.iot.ap-south-1.amazonaws.com";

// Obtain First CA certificate for Amazon AWS
// https://docs.aws.amazon.com/iot/latest/developerguide/managing-device-certs.html#server-authentication
// Copy contents from CA certificate here ▼
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAI3X69MTcFAg87ISkZ66G/Lg5k2rMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTA5MjUwOTUx
MjBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD8uoVLVbUVNGfRqdks
uKsKwre5cQ9TVEq3PveeQ2Oez5LFD6ooPlIvJmVxLtWi0EfQw71xV9OVOEpS7ulX
7Mmr1D4DjNEmcCOrZLPajG+yI03yaBuLN6te+pudwG+tjwqDzs6f10wJ0Jjw2KWT
lsMTePL3foBoQOHIv6UV/QWGX+NOtGFI9KigElHynPAwKI9To02RuRQuOnpuASMu
AjlmPMeuh4NsykuLfefc9hSm2y90lH0ROERH8mdAOlgOEwCViuJZnkEmRCTu+hs3
nQkTXy9kbA5Ba+no/7cBRvWdzDDDqdwhoHdYKZT/Id1o5O5tccfJ/ivYmWEY3N6Z
gcvnAgMBAAGjYDBeMB8GA1UdIwQYMBaAFJ/+a6NtfdzX0/3+/evRmwGx8R47MB0G
A1UdDgQWBBTrfodeHFUy7szb6gy7ldXjhRg5qDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEADr0hCGkntql/AjJmgrNPqz3C
zOiMzZtKCLgzghYLFGKs3B7Tga/ykgtIpQ9CGp0s1pVLRHH7buQ9HZTuGAZNll+9
3VVKwy87PF1hFeODaWU9jzC4gCj8RfWkKQVqaug/uv/om7J/kwQAsXaVN2Nez/8V
v+rdsXJdt+nBiMG1j+Mp8v4Dw7g0PtxhRt+l0FG8yaqIjA84b2yMP3Z+LFclifDH
wyvmOt1rLPhxjFUwxjKY8D6RXUrJ1NGENkjLhCKhacP/vmFFVM+5wMJ5Q3Khqke1
7uTe41bhHb4dUNK2LKn9WxJQbDw9pAYi3UpEHb6r1/SAHqyTyryFckbpr+pytQ==
-----END CERTIFICATE-----
)KEY";

// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA/LqFS1W1FTRn0anZLLirCsK3uXEPU1RKtz73nkNjns+SxQ+q
KD5SLyZlcS7VotBH0MO9cVfTlThKUu7pV+zJq9Q+A4zRJnAjq2Sz2oxvsiNN8mgb
izerXvqbncBvrY8Kg87On9dMCdCY8Nilk5bDE3jy936AaEDhyL+lFf0Fhl/jTrRh
SPSooBJR8pzwMCiPU6NNkbkULjp6bgEjLgI5ZjzHroeDbMpLi33n3PYUptsvdJR9
EThER/JnQDpYDhMAlYriWZ5BJkQk7vobN50JE18vZGwOQWvp6P+3AUb1ncwww6nc
IaB3WCmU/yHdaOTubXHHyf4r2JlhGNzemYHL5wIDAQABAoIBAGGv5x37fwc3Pnn4
YQ28Q8DhCwsO/JGFH2w9VpFCExuruFubdnYfwLyg5s0dAU7xmxDC2FMbU5l2LKRp
3KAz0rAsVdwhbiahaegyAKMVbYc5xkNQonTpi8Amtkf/viskAzh3k76NBcM1ciiG
VVn7CGRad+/aYd/qVFu4WCNrrdsGKL5dy8eLX9htBrkb5IIz8Va4urSymgU+KgJi
BYrQQyj8OwI3YWWkh1hDaP3WjfjDfyPDe8ffNwretFDnw+UrHaMekfOqGkkZt9cM
Okfposc1766Uwj29+e5aCDqOL+HXbL9LeocFdUIKE1DUm4WXY8nIPLPkQicgyGVf
0HreM2ECgYEA//o0roUdhtYg54j4PO1Q07bqZSDwEVSs+lMyA5iTjRrETkxCAEAW
oB0tYAGu4Q9WUqCL8AmypGj4wFXgF8bVqs4Z/y4Z09iKy7OJe2GbWY7UtKrY48w4
DgE1SooNYpvUjeXqf7PJS6HmyHjyRBPiQ6BsTZXoGXYsbNzfNKa9ynMCgYEA/MA9
yW3Jt7huVPeAlgOTbB0BK5GtLCnz3AWBeKCm11+RLDtR4sPddQ3BlOaPj5oXW3Dt
/1pHQzMzD6flYSxeQGm86Z14PWkCdu977e6gCVRZarZLz4VUSB1uwh3TKF788iYk
pKPYlS5dbJISNS5/hTxjEoRGriQk7Lv38glBF70CgYBaPJrbtuNsyAl7daaE2+f1
anMAyXa3tVDxQejMqbnCMWBodauCqRUQxphbUtySTDTTFfOe39xQ5wxhySQhXZ+v
Ac7aTScfriNnodfiXctE6/wB4IRq8XAFR9nAeCA11dc9WoKrF/brKZzQqQpGg3fs
/R2Q0Dqs1yLcEZTB29HmDwKBgQCPlerD9sHkxDqxvFVpY6ipf6S9iqm1cDPgJ6SQ
0btWmS0Q0rZHO/wgVmtF2uFttB1WzkX2jeP0Ei8M0tXlqV31+9vdX58CTBihVpWx
6qEyC6AsllllEBp8SXQ1hNoDkkriibbBbW9J+KgMWMNNQRgiqdaim1DH9zKe5n4K
GyXGhQKBgQCDMG51Ui84cXKFHOZl9yCy01SM4+kMQKpgkB7Cfe11vIUCebDswQLB
nO1G2tFWPfMb6cwz7MoR5h4r8l4KdYWaDOa2HjbwQRUIqNFa98mrIWgoaalUirQQ
Fb0K1iQeUsJy1lHSX35yxs5ghCiKPpS1NCGTI7lAIia1wyFFdbcUtQ==
-----END RSA PRIVATE KEY-----

)KEY";
