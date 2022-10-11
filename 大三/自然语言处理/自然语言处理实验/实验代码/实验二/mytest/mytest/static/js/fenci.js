var container = new Vue({
    el: '#fenci',
    data: {
        songci: ''
        // title: '词牌名'
    },
    methods: {
        send: function() {
            console.log($("#input").val())
            sent = $("#input").val()
            var self = this;
            var request = new HttpRequest('/hmm?text=' + sent);
            request.getJSON(function (result) {
                console.log(result)
                var data = result.result.replace('\t', '    ')
                $("#show").html(data);
            });
        }
    }
});