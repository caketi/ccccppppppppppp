import { get } from "./index_ajax";

const DEFAULTS = {
    method: 'GET',
    params: null,
    data: null,
    contentType:'application/x-www-form-urlencoded',
    responseType: "",
    timeoutTime: 0,
    withCredentials: false,

    success(){},
    httpCodeError(){},
    error(){},
    abort(){},
    timeout(){},
}
