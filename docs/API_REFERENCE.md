# 📘 `Masid/` – *API Reference*

Ito ang detalyadong talaan ng mga magagamit na API
(Application Programming Interface) ng aklatan ng **MuntingMasid**.

---

## Talaan ng API

<center>

| API | Paggamit |
| :-- | :-- |
| [`Masid`](#muntingmasidstream-stream-const-char-appname-severity-minlevel--debug-timestampfunc-tsfunc--nullptr) | Konstruktor – paglikha ng halimbagay |
| [`emergency(...)`](#mga-pinaikling-metodo) | Magsulat ng EMERGENCY log |
| [`alert(...)`](#mga-pinaikling-metodo) | Magsulat ng ALERT log |
| [`critical(...)`](#mga-pinaikling-metodo) | Magsulat ng CRITICAL log |
| [`error(...)`](#mga-pinaikling-metodo) | Magsulat ng ERROR log |
| [`warning(...)`](#mga-pinaikling-metodo) | Magsulat ng WARNING log |
| [`notice(...)`](#mga-pinaikling-metodo) | Magsulat ng NOTICE log |
| [`info(...)`](#mga-pinaikling-metodo) | Magsulat ng INFO log |
| [`debug(...)`](#mga-pinaikling-metodo) | Magsulat ng DEBUG log |
| [`setMinSeverity(...)`](#void-setminimumseverityseverity-level) | Itinatakda ang pinakamababang severity level na papayagang itala |
| [`setTag(...)`]() | |
| [`setStream(...)`]() | |
| [`setTsFunc(...)`]() | |
| [`resetLogCount(...)`]() | |
| [`getLogCount()`]() | |
| [`setTag(...)`]() | |
| [`getMinSeverity(...)`]() | |
| [`Masid::EMERGENCY`](#enum-severity) | |
| [`Masid::ALERT`](#enum-severity) | |
| [`Masid::CRITICAL`](#enum-severity) | |
| [`Masid::ERROR`](#enum-severity) | |
| [`Masid::WARNING`](#enum-severity) | |
| [`Masid::NOTICE`](#enum-severity) | |
| [`Masid::INFO`](#enum-severity) | |
| [`Masid::DEBUG`](#enum-severity) | |
| [`TimestampFunc`](#type-timestampfunc) | Opsiyonal na custom timestamp function |

</center>

---

## 🏗️ Konstruktor

### `Masid(Stream &stream, const char* logName, Severity minLevel = INFO, TimestampFunc tsFunc = nullptr)`

**Layunin:** Gumawa ng bagong `Masid` logger object na isinusulat ang mga log sa ibinigay na `Stream`.

<center>

| Parameter | Uri | Paliwanag |
|----------|-----|-----------|
| `stream` | `Stream&` | Stream object (tulad ng `Serial`) kung saan ipapalabas ang mga log |
| `logName` | `const char*` | Pangalan ng application na ilalagay sa log |
| `minLevel` | `Severity` | *Opsiyonal*. Pinakamababang log level na tatanggapin. Default: `DEBUG` |
| `tsFunc` | `TimestampFunc` | *Opsiyonal*. Function pointer para sa custom timestamp function |

</center>

---

## ⚙️ Mga Metodo

### `void setMinimumSeverity(Severity level)`

**Layunin:** Itakda ang pinakamababang severity level na ipapakita sa log.
Lahat ng mas mababa rito ay hindi ilalabas.

<center>

| Parameter | Uri | Paliwanag |
|----------|-----|-----------|
| `level` | `Severity` | Ang bagong threshold ng log filtering |

</center>

---

## Mga Pinaikling Metodo 

Mga pinaikling paraan para magsulat ng log sa partikular na severity level:

<center>

| Metodo | Layunin |
|--------|---------|
| `void emergency(const char* message)` | Log bilang `EMERGENCY` |
| `void alert(const char* message)`     | Log bilang `ALERT` |
| `void critical(const char* message)`  | Log bilang `CRITICAL` |
| `void error(const char* message)`     | Log bilang `ERROR` |
| `void warning(const char* message)`   | Log bilang `WARNING` |
| `void notice(const char* message)`    | Log bilang `NOTICE` |
| `void info(const char* message)`      | Log bilang `INFO` |
| `void debug(const char* message)`     | Log bilang `DEBUG` |

</center>

<center>

| Parameter | Uri | Paliwanag |
|----------|-----|-----------|
| `message` | `const char*` | Mensaheng ilalabas |

</center>

---

## Enum: `Severity`

**Layunin:**  
Tumutukoy sa severity level ng isang log message mula sa pinakamataas na
priyoridad hanggang sa pinakamababa:

<center>

| Value | Marka | Paliwanag |
|------|-----------|-------|
| `Masid::EMERGENCY` | `[KAGI]` | Pangkagipitan |
| `Masid::ALERT`     | `[ALRT]` | Dapat tugunan agad |
| `Masid::CRITICAL`  | `[KRIT]` | Malubhang error |
| `Masid::ERROR`     | `[MALI]` | Pangkalahatang pagkakamali |
| `Masid::WARNING`   | `[BALA]` | Babala |
| `Masid::NOTICE`    | `[PNSN]` | Karaniwang obserbasyon |
| `Masid::INFO`      | `[IMPO]` | Pangkalahatang impormasyon |
| `Masid::DEBUG`     | `[DALI]` | Debugging detail |

</center>

---

## Type: `TimestampFunc`

``` cpp
typedef const char* (*TimestampFunc)();
```
**Layunin:**
*Opsiyonal*. Tumutukoy sa function pointer na nagbabalik ng `const char*`
timestamp string (hal., `"12:34:56"`). Kung bibigyan, ito ay ilalagay sa
unahan ng bawat log.

---

> ## 📝 Tandaan
> 
> - Ang timestamp ay hindi awtomatikong nililikha — kailangang ikaw mismo ang
> magbibigay ng function.
> - Ang mga log ay lalabas sa format na:
>   ``` sh
>   TIMESTAMP [SEVERITY] [AppName] Mensahe...
>   ```
> 
>   o kung walang timestamp:
>   ``` sh
>   [SEVERITY] [AppName] Mensahe...
>   ```

## 📂 Kaugnay na File

- `src/MuntingMasid.h` – Ang mga deklarasyon ng API [dito](../src/MuntingMasid.h).

- `src/MuntingMasid.cpp` – Ang mga implementasyon ng API [dito](../src/MuntingMasid.cpp).

---

## 🧪 Tingnan din
Para sa mga halimbawa ng paggamit, bisitahin ang `examples/`
folder [dito](../examples/).