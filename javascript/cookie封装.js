// expires --
// max-age
// domain path -- 限定Cookie访问的范围 

const set = (name, value, { maxAge, domain, path, secure } = {}) => {
    let cookieText = `${encodeURIComponent(name)}=${encodeURIComponent(value)}`;
    if (typeof maxAge === 'number') {
        cookieText += `; max-age = ${maxAge}`;
    }
    if(domain){
        cookieText += `;domain=${domain}`;
    }
    if(path){
        cookieText += `;path=${path}`;
    }
    if(secure){
        cookieText += `;secure=${secure}`;
    }
    document.cookie = cookieText;
};


const get = name => {
    name = `${encodeURIComponent(name)}`;

    const cookies = document.cookie.split(';');

    for (const item of cookies) {
        const [cookieName, cookieValue] = item.split('=');
        if (cookieName === name) {
            return decodeURIComponent(cookieValue);
        }
    }
};

const remove = (name, {domain, path} = {}) => {
    set(name, '', {domain, path, maxAge:-1});
}

export{set, get, remove};