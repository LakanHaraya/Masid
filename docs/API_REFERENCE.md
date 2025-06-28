# 📘 `Masid/` – *API Reference*

Ito ang detalyadong talaan ng mga magagamit na API
(Application Programming Interface) ng aklatan ng **MuntingMasid**.

---

## 📘 Talaan ng API

[`Masid`](#muntingmasidstream-stream-const-char-appname-severity-minlevel--debug-timestampfunc-tsfunc--nullptr)
[`emergency(...)`](#mga-pinaikling-metodo)
[`alert(...)`](#mga-pinaikling-metodo)
[`critical(...)`](#mga-pinaikling-metodo) 
[`error(...)`](#mga-pinaikling-metodo)
[`warning(...)`](#mga-pinaikling-metodo)
[`notice(...)`](#mga-pinaikling-metodo)
[`info(...)`](#mga-pinaikling-metodo)
[`debug(...)`](#mga-pinaikling-metodo)
[`setMinSeverity(...)`](#void-setminimumseverityseverity-level)
[`setTag(...)`]()
[`setStream(...)`]()
[`setTsFunc(...)`]()
[`shouldLog()`](#shouldlog)
[`resetLogCount(...)`]()
[`getLogCount()`]()
[`setTag(...)`]()
[`getMinSeverity()`](#getminseverity)
[`getMinSeverityLabel()`](#getminseveritylabel)
[`Masid::EMERGENCY`](#enum-severity)
[`Masid::ALERT`](#enum-severity)
[`Masid::CRITICAL`](#enum-severity)
[`Masid::ERROR`](#enum-severity)
[`Masid::WARNING`](#enum-severity)
[`Masid::NOTICE`](#enum-severity)
[`Masid::INFO`](#enum-severity)
[`Masid::DEBUG`](#enum-severity)
[`TimestampFunc`](#type-timestampfunc)

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

### `getMinSeverity()`

``` cpp
Severity getMinSeverity() const;
```

**Layunin:** Kuhanin ang kasalukuyang itinakdang minimum severity level ng logger bilang `Severity` enum value.  
Ito ay maaaring gamitin sa kondisyonal na lohika upang malaman kung anong uri ng mga log entry ang papayagang ipalabas.

<center>

| Nagbabalik | Uri | Paliwanag |
|--------|-----|-----------|
| `Severity` | `enum` | Ang kasalukuyang log threshold na itinakda gamit ang `setMinSeverity()`. |

</center>

> #### Halimbawa ng Gamit
>
> ``` cpp
> Masid::Severity currentLevel = logger.getMinSeverity();
> ```
> **Sa halimbawang ito:**  
> Ipinakita ang retrieval ng severity bilang `enum` (lohika)
> 


---

### `getMinSeverityLabel()`

``` cpp
const char* getMinSeverityLabel() const;
```

**Layunin:** Ibalik ang kasalukuyang minimum severity level bilang *4-character string label* (e.g., `"IMPO"`, `"DALI"`), upang magamit sa user interface, log headers, o debug display.

<center>

| Nagbabalik | Uri | Paliwanag |
|--------|-----|-----------|
| `const char*` | `char array` | Ang string label ng kasalukuyang `minSeverity`, gaya ng ginagamit sa log output. |

</center>

> #### Halimbawa ng Gamit
> 
> ``` cpp
> Serial.println(String("Current severity level: ") + logger.getMinSeverityLabel());
> ```
> **Sa halimbawang ito:**  
> Ipinakita ang severity bilang `label` (user-facing)

---

### `shouldLog()`

```cpp
bool shouldLog(Severity level) const;
```

**Layunin:** Tukuyin kung ang isang log entry ay dapat i-output batay sa kasalukuyang minimum severity level (`minSeverity`).

Gamit ito upang **maiwasan ang overhead** ng pagbuo ng log message (tulad ng `String` concatenation, sensor reads, o mahahabang kalkulasyon) kapag hindi naman ito ipapakita sa log.

<center>

| Parameter | Uri | Paliwanag |
|----------|-----|-----------|
| `level` | `Severity` | Antas ng log na nais suriin kung papasa sa kasalukuyang log threshold. |

| Nagbabalik | Uri | Paliwanag |
| --- | --- | --- |
| `true` | `bool` | Kung ang `level` ay katumbas o mas mataas kaysa `minSeverity`. |
| `false` | `bool` | Kung ang `level` ay mas mababa kaysa `minSeverity`. |

</center>

> #### Halimbawa ng Gamit
> 
> ```cpp
> if (logger.shouldLog(Masid::DEBUG)) {
>    logger.debug("Sensor reading: " + String(analogRead(A0)));
> }
> ```
> **Sa halimbawang ito:**
> 
> Kung ang `minSeverity` ay mas mataas sa `DEBUG`, hindi na isasagawa ang `analogRead()` at `String` creation.

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