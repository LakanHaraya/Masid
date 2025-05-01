# 📝 CHANGELOG

Lahat ng mahahalagang pagbabago sa **Masid** ay idodokumento sa file na ito.

Ang format na ito ay batay sa [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) at sumusunod sa [Semantic Versioning](https://semver.org/).

---

## [Unreleased]

### Idinagdag
- Paunang bersiyon ng `Masid` class para sa structured logging gamit ang syslog-style severity levels.
- Suporta sa mga severity level: `EMERGENCY`, `ALERT`, `CRITICAL`, `ERROR`, `WARNING`, `NOTICE`, `INFO`, at `DEBUG`.
- Kakayahang gumamit ng iba't ibang `Stream` output (hal. `Serial`, `SoftwareSerial`, `File`).
- Opsiyonal na timestamp function (`TimestampFunc`) para sa custom na oras ng log entry.
- Opsiyonal na `tag` para sa karagdagang konteksto sa mga log output.
- Mga metodo para sa bawat severity (`emergency()`, `alert()`, `critical()`, atbp.).
- Kakayahang baguhin ang configuration gamit ang `setMinSeverity()`, `setStream()`, `setTsFunc()`, at `setTag()`.
- Tracking ng bilang ng log gamit ang `getLogCount()` at `resetLogCount()`.