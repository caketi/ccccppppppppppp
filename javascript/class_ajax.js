import DEFAULTS from './default_ajax.js'
class Ajax {
    constructor(url, options) {
        this.url = url;
        this.options = Object.assign({}, DEFAULTS, options);

        this.init();
    }
    init() {
        const xhr = new XMLHttpRequest();
        this.xhr = xhr;
        this.bindEvents();
    }
    bindEvents() {
        const xhr = this.xhr;
        const { success, httpCodeError, error, abort, timeout } = this.opotions;
        xhr.addEventListener(
            'load',
                () => {
                    if (this.ok()) {
                        success(xhr.response, xhr);
                    } else {
                        httpCodeError(xhr.status, xhr);
                    }
                },
                false
        );
    }
    ok() { 
        const xhr = this.xhr;
        return (xhr.status >= 200 && xhr.status < 300) || xhr.status === 304;
    }
}

export default Ajax;