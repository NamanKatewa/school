import socket, ssl, sys
from OpenSSL import crypto


def fetch_cert(host: str, port: int = 443):
    pem = ssl.get_server_certificate((host, port))
    cert = crypto.load_certificate(crypto.FILETYPE_PEM, pem)
    return cert


def print_info(cert):
    subj = cert.get_subject()
    issuer = cert.get_issuer()
    print("Subject CN:", getattr(subj, "CN", ""))
    print("Issuer CN:", getattr(issuer, "CN", ""))
    print("Valid from:", cert.get_notBefore().decode())
    print("Valid to  :", cert.get_notAfter().decode())
    print("Serial    :", cert.get_serial_number())
    print("Version   :", cert.get_version() + 1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python tls_analyzer.py example.com [port]")
        sys.exit(0)
    host = sys.argv[1]
    port = int(sys.argv[2]) if len(sys.argv) > 2 else 443
    cert = fetch_cert(host, port)
    print_info(cert)
