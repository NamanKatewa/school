from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from datetime import datetime, timedelta, timezone

# 1. Generate RSA Key Pair
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048
)
public_key = private_key.public_key()

# 2. Certificate subject and issuer (same for self-signed)
subject = issuer = x509.Name([
    x509.NameAttribute(NameOID.COUNTRY_NAME, "IN"),
    x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Haryana"),
    x509.NameAttribute(NameOID.LOCALITY_NAME, "Hisar"),
    x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Example Org"),
    x509.NameAttribute(NameOID.COMMON_NAME, "example.com"),
])

# 3. Build certificate
certificate = (
    x509.CertificateBuilder()
    .subject_name(subject)
    .issuer_name(issuer)
    .public_key(public_key)
    .serial_number(x509.random_serial_number())
    .not_valid_before(datetime.now(timezone.utc))
    .not_valid_after(datetime.now(timezone.utc) + timedelta(days=365))
    .add_extension(
        x509.BasicConstraints(ca=True, path_length=None), critical=True
    )
    .sign(private_key, hashes.SHA256())
)

# 4. Save private key
with open("private_key.pem", "wb") as f:
    f.write(
        private_key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.TraditionalOpenSSL,
            encryption_algorithm=serialization.NoEncryption()
        )
    )

# 5. Save certificate
with open("certificate.pem", "wb") as f:
    f.write(
        certificate.public_bytes(serialization.Encoding.PEM)
    )

print("Self-signed certificate and private key generated successfully!")
