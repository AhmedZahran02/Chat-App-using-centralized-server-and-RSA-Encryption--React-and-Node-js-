# 📧 Chat App Using Centralized Server and RSA Encryption  

This project is a **server-centralized chat application** designed to test and explore the performance and security of **RSA encryption** as key sizes increase. In addition to being a functional messaging platform, the app benchmarks the **time required to encrypt, decrypt, and break RSA keys** across different key lengths.  

---

## ✨ Features  

- 🔒 **End-to-End Encryption:** All messages are secured using **RSA encryption**, ensuring confidentiality between chat participants.  
- 🏗️ **Centralized Server Model:** Users connect to a central Node.js server that handles communication between clients.  
- 📊 **Benchmarking Encryption Performance:** Measure encryption, decryption, and breaking times for different RSA key sizes (e.g., 512-bit, 1024-bit, and 2048-bit keys).  
- 🌐 **Modern UI:** Clean and responsive front-end built with **React.js**.

---

## 🎯 Main Objectives  

1. **Implement RSA Encryption:**  
   Use RSA for secure message exchange.  
2. **Test RSA Key Performance:**  
   Analyze the **impact of increasing key sizes** on encryption and decryption times, as well as computational effort for breaking keys.  
3. **Provide a Functional Chat App:**  
   A centralized platform for secure and private communication.  

---

## 🛠️ Installation  

### Clone the repository  

```bash
git clone https://github.com/AhmedZahran02/Chat-App-using-centralized-server-and-RSA-Encryption--React-and-Node-js-.git
cd Chat-App-using-centralized-server-and-RSA-Encryption--React-and-Node-js-
```

---

## 📊 RSA Performance Testing  

- **RSA Key Sizes Tested:** 512-bit, 1024-bit, 2048-bit  
- **Benchmark Results:** 

| **Key Size** | **Encryption Time** | **Decryption Time** | **Breaking Time (Estimate)** |
|-------------|----------------------|--------------------|------------------------------|
| 512-bit     | Fast                 | Fast               | Breakable in modern systems |
| 1024-bit    | Moderate              | Moderate           | Difficult but possible      |
| 2048-bit    | Slower                | Slower             | Practically secure          |

> Note: Breaking RSA keys was simulated with timing estimates, not actual brute-force attacks.  

---

## 📦 Tech Stack  

### **Frontend:**  

- React.js  
- Material UI  

### **Backend:**  

- Node.js  
- Express.js  
- RSA Implementation (Custom + Node crypto)

---

## 🔧 How It Works  

1. **User Registration & Authentication:**  
   - Users generate public/private RSA key pairs on login.  

2. **Message Exchange:**  
   - Messages are encrypted using the recipient’s public key and decrypted with the recipient’s private key.  

3. **Performance Testing:**  
   - RSA operations are timed for various key sizes, providing insights into encryption, decryption, and breaking times.

---

## 🎯 Future Improvements  

- Support for **Elliptic Curve Cryptography (ECC)** for faster encryption.  
- Enhanced performance benchmarking with visualization charts.  
- Persistent message storage with MongoDB.  
- Add group chat functionality.  

---

## 🏆 Acknowledgments  

- **Node.js Crypto Module:** For RSA encryption and key generation.  
- **React.js:** For the modern and responsive UI.  

---
