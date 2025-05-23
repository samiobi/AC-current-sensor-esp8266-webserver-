# AC-current-sensor-esp8266-webserver-
# ⚡ مشروع مراقبة استهلاك الكهرباء باستخدام ESP8266 وZMCT103C

مشروع عملي لقياس شدة التيار والقدرة الكهربائية باستخدام وحدة **ESP8266** وحساس **ZMCT103C**، مع عرض البيانات لحظيًا على واجهة ويب محلية عبر تقنية إنترنت الأشياء (IoT).

🎥 **رابط شرح الفيديو على يوتيوب:**  
[https://youtu.be/nSgDnvBiPoU?si=GOXAD-GpRfnY5Uzy](https://youtu.be/nSgDnvBiPoU?si=GOXAD-GpRfnY5Uzy)

---

## 🧰 المكونات المطلوبة

- ESP8266 NodeMCU  
- ZMCT103C (حساس التيار)  
- مقاومات ومحول تيار  
- Breadboard وأسلاك توصيل  
- كابل USB  
- كمبيوتر مع Arduino IDE

---

## 📋 وصف المشروع

يقوم هذا المشروع بـ:
- قياس شدة التيار المتردد (AC Current)
- حساب القدرة الكهربائية المستهلكة (Power)
- إرسال البيانات من ESP8266 إلى صفحة ويب
- عرض المعلومات برسوم بيانية على متصفح الإنترنت
- التشغيل بشكل آمن مع التنبيه عند أي استهلاك غير طبيعي

---

## 🧪 خطوات التشغيل

1. تحميل الكود إلى وحدة ESP8266 باستخدام Arduino IDE.
2. رفع ملف الواجهة `index.html` إلى ESP8266 عبر `ESP8266 Sketch Data Upload`.
3. توصيل ZMCT103C بالدارة كما هو موضح في الفيديو.
4. الاتصال بشبكة Wi-Fi والولوج إلى عنوان الـ IP المحلي لمتابعة البيانات.

---

## 📺 شاهد شرح المشروع بالفيديو

[![مشاهدة الشرح على يوتيوب](https://img.youtube.com/vi/nSgDnvBiPoU/0.jpg)](https://youtu.be/nSgDnvBiPoU?si=GOXAD-GpRfnY5Uzy)

---

## 🔐 ملاحظة مهمة حول الأمان

⚠️ هذا المشروع يتعامل مع التيار الكهربائي، لذا يرجى اتخاذ جميع احتياطات السلامة الكهربائية. يُفضّل استخدام محول تيار معزول لضمان الحماية.

---

## 📄 الرخصة

هذا المشروع مرخص بموجب رخصة MIT — يمكنك استخدامه وتعديله بحرية مع ذكر المصدر.

---

## 📢 تابعني

- قناة اليوتيوب: [الإلكترونيات للجميع](https://youtube.com/@sami-electronics)
- البريد الإلكتروني: [أضف بريدك هنا إذا رغبت]

