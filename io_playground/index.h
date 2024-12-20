const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Web Control</title>
  <style>
    :root {
      --bg-color: linear-gradient(135deg, #C8102E, #54585A); /* Scarlet and Grey gradient */
      --container-bg: #fff;
      --text-color: #333;
      --button-bg-color: #000; /* Black button background */
      --button-hover-bg-color: #444; /* Darker black for hover */
      --button-text-color: #fff;
      --button-border-radius: 5px;
      --button-padding: 12px;
      --button-font-size: 16px;
      --container-padding: 30px;
      --heading-font-size: 22px;
      --section-padding: 20px;
      --section-margin: 15px;
      --top-container-margin: 30px;
    }

    body {
      background: var(--bg-color);
      display: flex;
      justify-content: center; /* Center horizontally */
      align-items: center; /* Center vertically */
      margin: 0;
      font-family: Arial, sans-serif;
      color: var(--text-color);
      text-align: center;
      flex-direction: column;
      padding: 0 10%;
      min-height: 100vh; /* Full height for the body */
    }

    .top-container {
      background-color: var(--container-bg);
      padding: var(--container-padding);
      width: 100%;
      max-width: 500px; /* Reduced width */
      border-radius: 10px;
      box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.2);
      text-align: center;
      margin-top: var(--top-container-margin);
    }

    h1 {
      color: var(--text-color);
      font-size: 28px; /* Adjusted heading size */
      margin-bottom: 15px;
    }

    .logo {
      display: block;
      margin: 0 auto;
      width: 120px; /* Reduced logo size */
    }

    .section-container {
      background-color: var(--container-bg);
      padding: var(--section-padding);
      margin: var(--section-margin);
      border-radius: 10px;
      box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.1);
      width: 100%;
      max-width: 500px; /* Reduced width */
    }

    h2 {
      font-size: var(--heading-font-size);
      margin-bottom: 12px;
    }

    .button {
      display: block;
      width: 180px; /* Reduced button width */
      margin: 15px auto;
      text-align: center;
      font-size: var(--button-font-size);
      color: var(--button-text-color);
      background-color: var(--button-bg-color);
      border: none;
      border-radius: var(--button-border-radius);
      cursor: pointer;
      padding: var(--button-padding);
      text-decoration: none;
      transition: background-color 0.3s ease;
    }

    .button:hover {
      background-color: var(--button-hover-bg-color);
    }
  </style>
</head>
<body>
  <div class="top-container">
    <h1>OSU STEM Playground</h1>
    <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAToAAAGQCAYAAAA+xazUAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA+dpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnhtcE1NPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvbW0vIiB4bWxuczpzdFJlZj0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL3NUeXBlL1Jlc291cmNlUmVmIyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ1M2IChXaW5kb3dzKSIgeG1wOkNyZWF0ZURhdGU9IjIwMjAtMDctMjJUMTg6NTU6NTErMDU6MDAiIHhtcDpNb2RpZnlEYXRlPSIyMDIwLTA3LTIyVDIyOjQ4OjE5KzA1OjAwIiB4bXA6TWV0YWRhdGFEYXRlPSIyMDIwLTA3LTIyVDIyOjQ4OjE5KzA1OjAwIiBkYzpmb3JtYXQ9ImltYWdlL3BuZyIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo4NzI0NzVFQ0NDNDMxMUVBODVBMEYwNjhBOEQzNkZEMiIgeG1wTU06RG9jdW1lbnRJRD0ieG1wLmRpZDo4NzI0NzVFRENDNDMxMUVBODVBMEYwNjhBOEQzNkZEMiI+IDx4bXBNTTpEZXJpdmVkRnJvbSBzdFJlZjppbnN0YW5jZUlEPSJ4bXAuaWlkOjg3MjQ3NUVBQ0M0MzExRUE4NUEwRjA2OEE4RDM2RkQyIiBzdFJlZjpkb2N1bWVudElEPSJ4bXAuZGlkOjg3MjQ3NUVCQ0M0MzExRUE4NUEwRjA2OEE4RDM2RkQyIi8+IDwvcmRmOkRlc2NyaXB0aW9uPiA8L3JkZjpSREY+IDwveDp4bXBtZXRhPiA8P3hwYWNrZXQgZW5kPSJyIj8+vHwDaQAAH9dJREFUeNrsnXm0XVV5wHduEiAQkhDAMEgHqYCu1T+qFgpI6aJWZQ6EIahUZpCQQBFCIkNeGEVQphBJmEPCLEMYLPOjuFwooLgqpRRBBBkFQaBlSEK6P84+5TW8d8/Z397n3DP8fmt9Kwzv5r23z7m/+33723ufYbf39xvIZLSNq21sz1BAj1hoY38b7zMU2Wy79db/7987DEkmq9m4CslBj/mGjctsjGQo/EF03Rlj4zobOzAUUAH2srEA2SG6mIx1mdy2DAVUiMk2LrexMkOB6GJkclfa2I6hgIpmdhcjO0QXwmgkBzXg6zYuQXaITis5uqtQF75maFAgOk9Wt3ENkoOaIXN2NCgyGMEQfMhYZbn6po2nbQxnCCESy2xsZGNVT9ktt7GvjfcYQkQ3GNJ40HRXX7Kxu42HbAxjGCESIqwv2VjkPoDzspd77X7IDtENVq5qJPeKjUk2fsotBAVwm8vSrnEfxHn5mvvQJbNbgTbP0Y12N5JvuSqZ3M5IDgrmX23sYeNtz9dJZifr7FZiCBGdfEpeq8jkXnSSe5BbB0rgDhu7mWQu2Ic9TdKgQHYtFp3Me1ytlNwuNn7ObQMly07E9SeF7C4zrLNrpejSHQ+axsOuNn7GLQM9KmOlJH1DUcbKouJV2j6AbWpGpI0H3zm5tPGQWa5OmDibtySoePmmWVlf8mOTNCiuc/dyXmhQtEh06WJgTSY3MSuTQ3AQSnoPZQgvnbO73lN2e7nq7Z9NS8+za4Po0jm5r3q+7kUnuZ8jOKiQ8O50srvW+K2z29Nldnu3UXZNn6PTSu4Fk9F4QHJQhvC6yE7E5TtnJ8tVZOlJ6+bsmiy6dFuXr+SkXJ3UrVxFclAB2UkZO1khO3lN6xoUTS1dQ3Y8SHf1wQDJyULkDQ1n+0N3hrn33+M2lnS737qUsenSE2lQ+Oyg2Mt9/31MSxoUTRRdYY2HHJIbb5KJ4s3czcseWMh6/91i45vdhJMhOyljdzf+DYrJ7v5sRYOiaaIb6yT3Fc/XxZiTW8vGjTa+yPsXPNjTvQ+lSfBOgOwmuczOt0Fh2iC7Js3RjTNJ46EXkvuEjZuQHCgRScnjDFfr9kUZ9+FdTlyvK0Qr28UaPWfXFNGlD7LRLCHZNUImd4ONLXm/QgC7OuGsGiA7bYNCZNfoBkUTRLe6UnIvm4xtXTkktwaSgwJkNypAdunSE9+DAKRBcZlp6N7Yuosu5BSSnUxYd1UaD4ttbMX7EwooY1cOlB2nnjREdGOd5DSLgXc24XNyNxvm5KC4zO7KwDL2Lic731NPZFHxFU3L7OoqutDGw0OBkqO7CmXILkaDQsTl26DYw5WxjZmzq6PoqtB42IL3IZTALia8QSFlbOt3UNRNdGOMbu/qS+6mCW08yBISGg9QdmYnpWRog0KyNE2D4vImlLF1El3aeNDMye0UKLk1TbKCHclBL8vYVQLL2EkK2e1hGtCgqIvoxjnJ+c7JPW+SxkPonNxiJAcVkJ1M2YTM2d3tZKc59SSzE4zowpCSUbOt63l3czwcILkJJmk8MCcHVWCiCW9QiOw0Oyh2NzXeQVF10aVHLX3Z83UxGg9rGxoPUE3ZLQiU3Z1K2Ulmd2kdZVdl0Y1xmZy28RAiubTxgOSgqmVsaIMi3RvrO2cn3djaNSiqKrq08aBZJxer8YDkoMrIh/miCLLTNihEtLVpUFRRdJJNXWd603iYYOiuQr1kJw2K0QGyu9tliJo5u0V1KWOrJjqRnKyT852Te97NXcRoPGzO+wdqxM4uuwqR3T2ujP2j5/fezZWxoxBdfsa5Tydt4yFEcmsjOagxE53sQreLTTYN3S5WFdGlOx58y9UXTZzGA5KDJshuoQmfs9PsoEgXFVdWdlUQXXoKSS8aD7J39VbDnBw0R3ahp56kc3a+p57sbircoOi16KRc1TYedjLhc3Jy1BLdVWii7ELKWJmzk/k33x0U8ppKNih6Kbp0x8M/KSQn5eojgZJjxwM0lZ1dGRvajZWStBENil6JLj1PTtt4CFlCQuMB2pLZ9fo8u8rIrheiGxMgObl4IY0HOf78JiQHLcvsQubs7jENaFCULTrJ5ORBu9o5udC9q7dSrkILM7sYDQqZLtLM2Yloe96gKFN06Y4H3zm535t4jQcyOWhrZieyC5mzu9eJy7eMneS+d08zu7JElzYevqTI5OST5BcBklsHyQF8KDvpiK4eoYx9TSG7zMc41l10aePBN5OLseNB1sn9yMZm3OcAH1ZGoUc8SRmr2UEh6+wu65XsihZdSOMh9JGE4w3r5ABWZKLL7ELn7ERcmkcp9qRBUaToxrlsyrfxIHNyO5rwJSQ0HgCGLmNDGxT3uIpL26Ao9Ty7okSXNh585+R+7y5CyGLgdU3yjAfm5AC6y06qrRgNCt9FxZNMjrP0qi46KRmvVUouRuNBFgP/HfcxQCY7mvBubEiD4vKsrLKqokuPWvKVXIzGgzytS57xQOMBwE92oTso0vPstA2KwmUXU3TpMx58Gw8vmPCTgeX4c3Y8AOjL2BhzdpoGRSlPF4slunTHg6/k0sXAoc9dvQXJAQSxk+ldg2KSKbhBEUN0Mien3fEgre6QxgOLgQHiZnbSoAhZVHyvE1elGhShohtvdDseYklOylUaDwDx2NGE76AQ2YXsoIg+ZxciunTHg6/kZE4u9Dy5tZ3kaDwAFCO70PPs0m6s9jy7qLLTii49/lxzaKakxyHd1TVduYrkAIpjJxO+g0IyO02DYjcTuUGhEZ0sBr7e6ObkdjThp5DIjgfm5ADKkZ1UbSFLT+51FZzm1BMRbZQGha/oxjvJ+Zarz7lM7pcBkksbD8zJAZRbxobuoLjPZWm+c3a7mkgNCh/RpY2HbRSZXOiOB9nWxZwcQG/YwSRLT0IbFHuaHjUo8opO23hIdzyENh7Y8QDQ+8wuxg6K3RVlbPADd/KIThoPmnVyz5vwU0jkPLnFlKsAlUDm7K4KlN19LkvTnnqikl2W6KTx8COjm5Pb0YQ/kvA2JAdQucwuxpydpkGRztl5Nyi6iS5tPPyj59/5rAlvPMicnDQeNuW+AqgcMebs+l1m5ztnt4vLKr3m7DpdJCfr5HwbD88568aQHHNyANXO7EJlJ5mdLCp+VSG7zCPhs0QnjYdrFJncCyZe4+FvuY8AapHZLTLhh3dqHpLtdZ7diqJLdzxontYV+khCkRyNB4B6Zna9aFCkp55k7qAYKLq08eDbXY3VeLgFyQHUVnZXmd40KHYxOZ4bm4pO9o9qGw+SyYXMya3nJMecHEC9ZSfd2DEBsus3yfSXZs6u61l6HSc5beNBvsGjAZJLGw/MyQHUn+1N+BFPIjttg+KKoUrojrOwr+SeN+HbuuRkYHmQzRe4PwAaQ4wGRdqN9T3iSbLBBYNllSK6XjyScG3KVYBGl7GZa90KalCI7GYPJjofnjXhjQc5hUSOWmIxMECzM7trAjO7flc5+mZ2G4SITiQnx5+HzMlJ42ExkgNojexiNCgks/OZs1uiFd2zzqyh58nJUUs0HgDaQ6wGhRzx9Ir2h8gjuv+xMdmENx7orgK0N7OLcZ7dwYNla7FE96aNfw/4JdemXAVAdibHDooMHrfxblGik69ZWWlhWScnRy3RXQWAtEGxutInK9kYVpTotKSNB8pVAEiRObvMBkVsgkTXxb7rm2ROjsXAALAi27kydpwiqytfdEMgm2uvQHIAkJHZzdWWolUQnZyCsgnXEQAy2NQUO332f4wo4O/8wMb7XMPSkLGWJUDDbSxnONRIZrHMJBPlwxmOUnivrG80grGuNb+xsZ+NP9gYyXBE+dDYyMZlJnmcADQERFdfnjbJlrzHGIqoPGGSjeFyCO2aDEcz6DAEteR3JjnwFMkVw/0meY7oGwwFooPe8FuTdKyQXLH0m2Qz+Z8YCkQH5fKUSVaXI7lykP2Vcvbi6wwFooNyeNIkZwH+B0NRehkrc6GvMhT1hWZEPZDGgxyT9XjWF7580yxGy4Ocq/D/zZWx8sxhGhSIDgrgGZOj8YDgdKTjlkN4IjtpUMhzTsYxcogO4iGNhx26lasIrlTh9bvMWg6QHcuo1Qfm6KqLLAbeHsn1RngZsqNBgeggAk+6cvVxJFdJ2dGgoHSFCOXqLhEkJ1uY2Pvande7jXFGGZs2KG40bBdDdOAtudA5uVE2LrGxNaLrimziv87G4YGy29XJbg2GFNFBNk87yYVkcnLk/RUu04BspjnhTQuQ3f3mowYF3diKwhxdNXgyguTkwNMrkZw3U22c1+0LPObsXmM4ER0MLbnQxoOUqwtdGQX+HGbj7Aiyk8yOBgWig0HKVckE/jPgDbaqjcvJ5II5PILsHnDXgcwO0YFDGg9d967mzOREcrsznNFkd06g7NJuLEc8IToyORO+GDhtPOzGcEZFGhMx5ux2QXaIrs086SQX2ni4inK1MGTObk6g7PpNMvfKnB2ia6XkpFwNnZNb6DIGKI4pEcrYBwwNikrAOrpyy1VpPDwRKDlN40FK5LdNu59utdTGWjY29CxjhZBFxT9xsrvRfX9AdI0lVuNhgUJyMo8na8XkCVfDWnwN5DGca7hseBtP2WUuKha6CE9kJ3OpLCpGdI3lKSe50B0PmnVyi0zyOMSlXIYPeXFAduUju6kuG56SVcp2kV26qJjtYj2AObpiibnjwVdyIsZ9kNzHeNNlxfd6vu5Qk9GNzXE9RXY0KBBdo3jCxGs8+EruCjK5rsiyD1l7eI/n66Qbe26g7H7irufLXAZE1wSuNeGNB82cnLxmXxtLuARd+aONPRSymxpBdtKNvY1LgOjaziijO4UkzeSWMYS5ZacpYzMPAsjBBww/omsCw5Sf9tJ4WBRQriI5P+QB1ROVZez5AVndMIYe0bWVdMeD72LghYY5uRDeMsnyD1/ZSYNiDsOH6CD/p/xYl8n5Sm4BkouCNChkzu5uz9dNcWXsSIYQ0UE2eweUqzQe4qBtUEgZuzPDh+ggmzEKyUl3lTm5uMgDczQNijEMHaKDbHyEheSKRdOg4FogOojIlYbuahm8pczsANFBBH5gaDyUmdmdwzAgOigfunvlMpwhQHRQPiw0ZbwB0QEAIDoAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdAACiAwBEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAIDoAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdACA6AABEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAogMAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdACA6AABEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAogMAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdACA6AABEBwCA6AAAEB0AAKIDAEB0AACIDgAQHUMAAIgOAADRAQAgOgAARAcAgOgAABAdAACiAwBEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAIDoAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdAACiAwBEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAIDoAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdAACiAwBEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAogMAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdACA6AABEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAogMAQHQAAIgOAADRAQAgOgAARAcAgOgAABAdACA6AABEBwCA6AAAEB0AAKIDAEB0AACIDgAA0QEAogMAQHQAAIgOAADRAQAgOgAARAcAgOgAANExBLVjGUPAeAOiazrjGIJSWZ0hQHRQPmfZ2JhhKIXP2ziJYUB0UD6ftbHYxkYMRaF8zsYtNv6CoUB0EI+RHl8rkrvVSQ/i8wUbt9tYt6DrB4iutTzm+fWftnETsitEcjfbmODxmvdsPMnQITpwTJg4e6j/daONw20s95TdDTY2YWSj8Hk3nut5Su4AG/czfIgO8nGujSM8X7Oxy0BoUIRLTsZxA4/XvG9jfxsLGT5EB/mzulR2vpmdzNktRnZBkpPGw/oer1liYz8bi5TXGRBdI1gamNlN83wNDQodMid3m/FrPMi13beb5Aq+PwDRVYa1ArI6YY6NqZ7f868MDQpfyfk2Ht7PI7kc13dNhh/RNYH9XZQtO2lQSGPjM1yCzHJVxsm38SDl6sLA63qUjYlcAkTXBEbZmO/eGKGy08zZSWZHN3ZoyUkm90nPTG7/CJnct22cYWMElwHRNWl8Y8gunbPTNCiQ3cfLVZnL9Gk8xCpXp9s4k0tQPnyqFM9wJzvhkm5vkpdvmpWV2S13f/qUsdJNlHVeb9hYqcXX4V2Xwck1WMfjdUuc5K6MILnTeTsguqbLbp6NYTYuDpDd+QOklxdpUPRzCVS858pVJEfpCh4fKheY8AbF+cZ/6QnoJLdfhHL1KCRHRtfG8U7L2JDM7jyXHZ7t/oS4vB8pk0sbD1AyP77/fjK6CmTR8yJkdtKgkKUnyxnS6JLbx9B4oHSFYIZHkp2UsYchu6iSk8bDVYHX5RjKVUQHH8kuxpzdXCc7CONdl8nFaDx8l+FEdPARI1xmd0AE2VHG6kkbD6GZHI0HRAcFl7GaHRQQV3I0HhAdZFyHGLKTbixLT/ITczEwkqt46QTVyuxkuchF3d50OXZQvGXjKyaZd4LBWdkkm/qvD5ScNB6Yk0N04Cm7C9w/h8juchcQAJKjdIXiZXdg4JsQipXc0UgO0UEc2YV2Y6E4yX2PkaJ0hTgfQvPylLFCRikLcQRHuYrooCDZZc7ZIbxSBCfMsHEaI4booJgy9ocm6cZeGPFNC35MR3L1zhigHh9IIrsDGIqeSY4dD4gOSsrsZM7uQIYCyQGia/r1ylx6AtGYgeQQHSC7JjPTMCeH6KDn103m7A5iKArL5E5lGJoDXdf6knZj5clWz9gYyZAEIV1tOXjzsyY5Ah0QHVQoszueYYAaf7jUtnSVH35VriEAZCDPGS7l/MQiRPeqjcu4hgCQgSyX+qCuoltqkv2AZ3EdAWAITjBDHFZaxDbGINF1+YEkHT3SJM8dBQAYSJ+Nk8r8hnlFp62j/4XMDgAGINnRbEXyVLjoRHLvBvxgktn9gOsL0HqOs3FiwOvVjwbII7q1TPKUJE0Jm/JtZAfQesmdEuiRb9oYVZToZGGqzLUdFEF2lLEA7eP4CJLrs3Gs81Ehoktll3lyRs4yFtkBtAeRwsmB3jjB/T1qfLuumc8eRXYAMCCTOzHQF/J3+J4mu0qo6GTXw/xImR1zdgDN5bhImZxv80Kap4sHE93JiixQjgk6OPCXoEEB0ExkLi3GnJzmuQCH2bh0MGlJauh77pa8bm4k2VHGAjQHycJOjSA5zZzcVOclM1Tp+h3j/wi3XAdAMmcH0BrkzX5SoA+OV0hOytVpNuZ0k1WKnKiqOTY6VjeWMhagvsRoPGjn5A63cV5WVjaQGVm19SAMc5ldjHV2Z3K/ANQOmZMLbTx03RrWRXKHZUluMNEJmd2SIf4eOe32kMBf9mgb3+e+AagNMu0VOicngutTfG+R3Ny8ghoqDfXN7NIGRajsjkJ2ALUpV08LfL/3uZJVk8nNzfuCbuvoJLPzbVAMc5ld6JydyI45O4BqS65XOx5kTu583yysGzMVshNiNChYZwdQTU6IJDnNnJx0V8/z/YHz7IyYaXQNCpFdjAYFZSxAdZA5udAlJIU2HrSiS8tY3xNB0zL20AhlLN1YgGpILnROTpaP9Cm+9xTjMSenFV2udHWIv18W8X0rcHCORnYAPeXYCJKTLM738ZzLneR+GPLD+27qlx9S06CYG6GMZekJQG+Isa1rltF1V6eFZHJa0Qkzs37pIYixXYwyFqBcMqetckrOt1wVyU01XbZ1meQ4pj+38Skb42OLLk1jtTsoQg8CILMDKIfMRmTOdXIayUm5OtQSks1sXGTjFzZ+6UL++XYbk03yYOwoostl+iHEKrV26JwdmR1AsWQe9JGz8aBZJ3eoGXxOTp4Xca6NB01yAPAmNpbYeNvGBBvb2rjKRr+Nv4klurR212R2YuoY28WQHUB8etl4OMxVfiuyuo0bXDn7so0jnOjWdyEl7F42fmpjc5fdbRpLdGlm5ztnly49iVHGIjuAeBxv4pwn59t4+MBJbKhyVX6mr9p4yMbWNu4yyRzdX9v4nI31bNxpY0sb59hYx2V342OJLv0E0DQoRHYxurHIDiBOuRq646FPUa5mSW4Lk8zZvWRjZ1eqSub2sEnm5h4xyTzd0yZpXhzpsr9PuX+OJrpUdppFxZKmxlhndwb3KYCamZHKVc2hmVkb9Pd3rpADel+0sYaNsTaes/ENkzzv9UD37yLEL9qYbuM9GwfI13ciD5bm4Lx0zi5UdtORHYBacqGNh5MU5aowVOMhZTUnrmU2bhkgR+F3NhbZWGCSLuwC998/Y+MpV+ZKk+LLnQIGTUZE26CIITvKWID8ZJ5SlLO7epwik5tiBm88DOQTNta18YKNZwb896U2NnZZ6HHOOzPd/3vc/fkr9+dWnQIHT9OgiPHAHebsAPKRee5kzjk53+5qOieXZ8fDSJOsi3vHyW3g3zHOxpdcNik/xyOuhH3Afc07aVbYKXAQaVAAVJcYx5/3Gf2DbPKeJ/emjdddVjduwH8X+T1qkiUk6UkoV7sSNi1t/8z9+ZtOCYPpexxLzAbF97ifAT7GDBO+hESzGPgD9772OTTzFRGVSdbRbTGIK0RqcnTTi+79voH7f2Pc18uC4ps7JQxqn9E3KEKPeDoG2QF8THKnB76vTjK6xcDyfp6nkOOV7p/TTQbL3J+jbQy38ZpJGpHjzUcNyb1tfNLGfTZ+Pfzr++xTxuD22xhh4+89Zbe9jT+YpHsyKP89+R/M6Kvv7/b33G2Szs2W3ONAuRqlu+rbeBBZDbXjIQ9PmGT93OYuQ7vNxhs27jAfNRx+7bK//zLJVjGZAlvZZZC/LUt0xpl1pKfsjJOdLBR8JEB2dzn7b8G9Di2WXIyndWkbDyHnyb1v4zEbk0yyn3VNl7k9vMLX/MzGp02y5ES+RuYgL/kwa7q9v7/sAT/ZDbom7e36iTBhYuZ0oJSxR3PPQ8uIcTKwvLm027rmRvo9trNxuY21XEYnydOjTnKyC2IbGxu6rz1lYObZC9EJfUbXrck8aTSH7GR+Yjr3PrSEzHnqnI0HzZyclI3zIv8+f+kSpd1Msjtixe/5gMtc7xj4P3olOu0nRHoY3/lkdgCZxNjxUFgFFoicVrKpE58sNZGu669WKGcrITqt7IzJ8aAMMjtAcj1rPOTZ8VAqnR5//1lGt6g4xnl2ktKzNxaaSIzuqmZbVzond0HVBqRTkYtykuJ1cyPIbrphnR00i1iLgTXd1aBHEjZddMboTz2Za+IsKj6d9wc0gOmmt4uBL6jqwHQq9LNonhSU7qA4LPDiZq4WB6hBJndG4PvgZKM7hUQqq3lVHpxOxX6e2coy9rwImd0MylioKTMjZXK+3dUP3PtuftUHqFPBn0nzwB1j4pxnR4MC6kaM8+RmmwY1HuoiuvTinah4XawGBWUs1IFjTPh5cpqTgSvdeKiT6IRZxv+Ip1R2zNlB08lcMVDQnFx61NIFdRqsTsV/vj7jv1VMGhTnITtouORCGw+SCWp2PIjk5tdtwDo1+BlPNPoGxZQIsqNBAVViponTXf2OIpOrReOhrqIzbg5BI7s5Jk6DAtlBVSQXY8eDprtauW1dTRRdiOxidWMpY6HX5WqMvavaHQ8X1HnwOjX7eUV2mjm7WA2K7/J+gx6Q+YD2nHNymsbDIXWXXB1Fl6befYrXyZzd1MCbJXNhJkABkjsz8L6Vva++c3LpjocLmzCInZr+3LONbp3duWR2UCNmRJDcKeajBzvnRR4+862mSK7OojOuhNV2Y0Pn7DInhQECyZwXzjknp+muSjIwr0mD2an5z3+C0S0qjvEoRZHdabwfoQB6tRh4man4KSRtFZ3QZ3QNihinnmQ+dATAk6NMeONB5uQ0S0iKeMYDootISINiGrKDCmVy348gOd85uVRyFzZ1YDsN+l1mK8vYc8jsoAJknpxTUOMhldz8Jg9up2G/j2R1vdouJrKjQQFaycWYk/NtPKRzcvObPsAjGvg7SYNiqSK7m+P+PL/bzZbxdDH5NH3XJA/aXcr7F3K8/662cVaETE4juUaXqwPp9eMOixaeppSd5jK8IcnxKEWAKOSQnEyZzFCUqwfbuKgt49hp8O8mDYpZitfJouLDA28+ACSH6EqVnSb9OtuEz9kBFCm5UxWSS8vVi9o2niNa8Dv2OaH7ntqQa86OUhZKFpwgjQfNti758J7fxnEd0ZLfs7AGBcKDEgUn0HhAdJllrMxP+C4/mePG6ZyINyuABlm+dIzna9I5uYvbPHCdlv2+JytKWEHm7A7nfQY95HSF5CSTO6jtkmuj6FLZaRsUU3m/QQ+Q7up0Zbl6McPXTtEJfUa3N1aWnkzhtoES0XZXZcfDhQxfwogW/+6S1S03BTUoACJlchrJycnAFzF8ZHQp0qA4TvE6kd0R3D5QIKcbFgOT0UVE2vXDFZmd7E9cyca9NkYxjBCJd2zsZeNIheRoPCC6zMxODuPsU3zqLiEzhoiIsEZ6vkbWiB6K5BBdHtKMzld2Ixk6iMhwz6+n8ZADMpGPy+4EhgFqgkjuYCSH6DTIzoljGQaoQYnLnByiC0LWLrGfC6qcyYnkLmEoEF0o2vPsAIpEGg+HkMkhutiy40gSqFImJ40H1skhuuj0Gd2iYoAiylUaD4iuME5BdtDjcvVAw5ycGtbR+clutI2tTPKkL4AyWMXG9TYuZSj0/K8AAwA08n+0WjZYUQAAAABJRU5ErkJggg==" alt="Ohio State Block O" class="logo">
  </div>
  
  <div class="section-container">
    <h2>Single Component Webpages</h2>
    <a href="/led_control" class="button">LED Control</a>
    <a href="/thermometer" class="button">Temperature</a>
    <a href="/force_sensor" class="button">Force Sensor</a>
    <a href="/dc_motor" class="button">DC Motor</a>
    <a href="/servo_control" class="button">Servo Control</a>
  </div>

  <div class="section-container">
    <h2>Multi-Component Webpages</h2>
    <a href="/dc_motor_temp" class="button">DC Motor & Temperature</a>
    <a href="/pressure_led_control" class="button">Force Sensor and LEDs</a>
  </div>

  <div class="section-container">
    <h2>Extra</h2>
    <a href="/meet_the_team" class="button">Meet the Team</a>
  </div>
</body>
</html>
)rawliteral";



