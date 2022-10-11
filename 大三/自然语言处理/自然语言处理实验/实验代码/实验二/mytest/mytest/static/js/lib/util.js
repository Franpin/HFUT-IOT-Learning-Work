function HttpRequest(baseUrl, query) {
    this.baseUrl = baseUrl;
    this.query = null;

    if ( query ) {
        this.query = query;
    }
}

Object.defineProperty(HttpRequest.prototype, 'url', {
    get: function() {
        return HttpRequest.makeUrl(this.baseUrl, this.query);
    }
});

HttpRequest.prototype.getJSON = function(callback, error) {
    getJSON(this.url, callback, error);
}

HttpRequest.prototype.postJSON = function(data, callback, error) {
    postJSON(this.url, data, callback, error);
}

HttpRequest.prototype.postFile = function(selector, callback, error) {
    var $selector = null;
    if ( typeof(selector) == 'string' ) {
        $selector = $(selector);
    }
    else {
        $selector = selector;
    }

    var file = $selector.get(0).files[0];
    var formData = new FormData();
    formData.append('file', file);

    $.ajax({
            url: this.url,
            type: 'POST',
            data: formData,
            cache: false,
            contentType: false,
            processData: false,
            success: function(data) {
                callback(data);
            },
            error: function(req, message, e) {
                console.log(message);
                console.log(e);

                if ( error ) {
                    error(req, message, e);
                }
            }
    });
}

HttpRequest.makeUrl = function(baseUrl, query) {
    if ( !query ) {
        return baseUrl;
    }

    var queryString = HttpRequest.makeQueryString(query);
    if ( queryString.length == 0 ) {
        return baseUrl;
    }

    return baseUrl + '?' + queryString;
}

HttpRequest.extractBaseUrl = function(href) {
    var queryPos = href.indexOf('?');
    if ( queryPos == -1 ) {
        return href;
    }

    return href.slice(0, queryPos);
}

HttpRequest.makeQueryString = function(parameters) {
    parameterList = [];
    for ( var key in parameters ) {
        var value = parameters[key];

        parameterList.push(key + '=' + value);
    }

    return parameterList.join('&');
}

HttpRequest.parseQueryString = function(queryString) {
    queryString = queryString.substring(1);
    if ( queryString == null || queryString == '' ) {
        return {};
    }

    var parameterList = queryString.split('&');
    var parameters = {};
    for ( parameterIndex in parameterList ) {
        var parameter = parameterList[parameterIndex];

        var keyValue = parameter.split('=');
        var key = keyValue[0];
        var value = keyValue[1];

        parameters[key] = value;
    }

    return parameters;
}

function Response() {
}

Response.prototype.redirectTo = function(request) {
    location.href = request.url;
}

var Application = {
    showPage: function(page) {
        var queryString = window.location.search;
        var baseUrl = HttpRequest.extractBaseUrl(location.href);
        var query = HttpRequest.parseQueryString(queryString);
        var request = new HttpRequest(baseUrl, query);
        var response = new Response();

        page.request = request;
        page.response = response;

        if ( 'onInitialize' in page ) {
            page.onInitialize();
        }
        if ( 'onShow' in page ) {
            page.onShow();
        }
    }
};

function postJSON(url, data, callback, error) {
    $.ajax({
        url: url,
        type: 'post',
        contentType: 'application/json',
        data: JSON.stringify(data),
        dataType: 'json',
        success: function(data) {
            callback(data);
        },
        error: function(req, message, e) {
            console.log(message);
            console.log(e);

            if ( error ) {
                error(req, message, e);
            }
        }
    });
}

function getJSON(url, callback, error) {
    $.ajax({
        url: url,
        type: 'get',
        contentType: 'application/json',
        dataType: 'json',
        success: function(data) {
            callback(data);
        },
        error: function(req, message, e) {
            console.log(message);
            console.log(e);

            if ( error ) {
                error(req, message, e);
            }
        }
    });
}

function toJSON(object) {
    return JSON.stringify(object);
}

function fromJSON(data) {
    if ( !data ) {
        return undefined;
    }

    return $.parseJSON(data);
}

function redirectTo(url) {
    window.location.href = url;
}

function disableAll(e) {
    e.preventDefault();
    e.stopPropagation();
}

function formatDate(date) {
    return '' + date.getFullYear() + '-' + 
        paddingZero(date.getMonth() + 1, 2) + '-' + 
        paddingZero(date.getDate(), 2);
}

function formatDateTime(date) {
    return '' + date.getFullYear() + '-' + 
        paddingZero(date.getMonth() + 1, 2) + '-' + 
        paddingZero(date.getDate(), 2) + ' ' +
        paddingZero(date.getHours(), 2) + ':' +
        paddingZero(date.getMinutes(), 2);
}

if ( !String.prototype.repeat ) {
    String.prototype.repeat = function(count) {
        if ( count <= 0 ) {
            return '';
        }

        var result = '';
	for ( var i = 0; i < count; i ++ ) {
	    result += this;
	}

        return result;
    }
}

function paddingZero(number, width) {
    var numberString = String(number);
    if ( numberString.length < width ) {
        numberString = '0'.repeat(width - numberString.length) + numberString;
    }

    return numberString;
}

function getDateOfDatePicker(widget) {
    var $widget = widget;
    if ( typeof(widget) == 'string' ) {
        $widget = $(widget);
    }

    var dateString = $widget.val();
    return fromDateString(dateString);
}

function fromDateString(dateString) {
    var year = Number(dateString.slice(0, 4));
    var month = Number(dateString.slice(5, 7)) - 1;
    var date = Number(dateString.slice(8, 10));
    var hour = Number(dateString.slice(11, 13));
    var minute = Number(dateString.slice(14, 16));

    return new Date(year, month, date, hour, minute);
}
