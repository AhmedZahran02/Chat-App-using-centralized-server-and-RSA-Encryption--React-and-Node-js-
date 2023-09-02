class MOAOZMATH {
  rotateNumber(x, mod) {
    if (x >= 0) {
      return x;
    }

    let cycles = Math.floor(Math.abs(x) / mod);
    x += mod * (cycles + 1);
    return x;
  }

  GCD(a, b, Quotients) {
    if (b === 0) {
      return a;
    }

    let q = Math.floor(a / b);
    let r = a % b;
    Quotients.push(q);

    return this.GCD(b, r, Quotients);
  }

  modularInverse(a, n) {
    let Quotients = [];
    let X = [1, 0];
    let Y = [0, 1];

    if (this.GCD(a, n, Quotients) !== 1) {
      return 0; // Modular inverse doesn't exist
    }

    for (let i = 0; i < Quotients.length - 1; i++) {
      let nextX = X[i] - X[i + 1] * Quotients[i];
      let nextY = Y[i] - Y[i + 1] * Quotients[i];
      X.push(nextX);
      Y.push(nextY);
    }

    return this.rotateNumber(X[X.length - 1], n);
  }

  gcd(a, b) {
    if (b === 0) {
      return a;
    }
    return this.gcd(b, a % b);
  }

  bs(start, end) {
    let phiN = end;
    end = phiN - 1;

    while (true) {
      let x = Math.floor(Math.random() * 100);
      if (x > 10) {
        if (this.gcd(start, phiN) === 1) {
          return start;
        }
        start++;
      } else {
        if (this.gcd(end, phiN) === 1) {
          return end;
        }
        end--;
      }
    }
  }

  generateKey(p, q) {
    const n = p * q;
    const phiN = (p - 1) * (q - 1);
    let e = 2;
    e = this.bs(2, phiN);
    const d = this.modularInverse(e, phiN);
    return [e, n, d];
  }

  noramlModularPower(a, b, mod) {
    let ans = 1;
    while (b--) ans = (((ans % mod) * a) % mod) % mod;
    return ans;
  }

  mulMod(a, b, m) {
    if (m === 0) {
      return a * b;
    }

    let r = 0;

    while (a > 0) {
      if (a & 1) {
        if ((r += b) > m) {
          r %= m;
        }
      }

      a >>= 1;
      if ((b <<= 1) > m) {
        b %= m;
      }
    }

    return r;
  }

  fastModularPower(a, n, m) {
    let r = 1;

    while (n > 0) {
      if (n & 1) {
        r = this.mulMod(r, a, m);
      }

      a = this.mulMod(a, a, m);
      n >>= 1;
    }

    return r;
  }

  converter(s, e, n) {
    let out = "";
    for (let i = 0; i < s.length; i++) {
      let val = s.charCodeAt(i);
      let encrypted = this.fastModularPower(val, e, n);
      // console.log(encrypted);
      out += encrypted.toString();
      out += "-";
    }
    return out;
  }

  encrypt(value, e, n) {
    //logic
    return this.converter(value, e, n);
  }

  separateString(buffer) {
    const len = buffer.length;
    const Message = [];
    let number = "";

    for (let i = 0; i < len; i++) {
      if (buffer[i] === "-") {
        Message.push(Number.parseInt(number));
        number = "";
      } else {
        number += buffer[i];
      }
    }

    return Message;
  }

  decrypt(value, d, n) {
    const ans = this.separateString(value);
    let out = "";

    for (let i = 0; i < ans.length; i++) {
      out += String.fromCharCode(this.fastModularPower(ans[i], d, n));
    }
    return out;
  }
}

module.exports = MOAOZMATH;
