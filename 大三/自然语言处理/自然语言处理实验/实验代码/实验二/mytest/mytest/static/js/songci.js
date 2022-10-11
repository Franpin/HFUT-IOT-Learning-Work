var container = new Vue({
    el: '#chat',
    data: {
        songci: ''
        // title: '词牌名'
    },
    methods: {
        ask1: function() {
            console.log('1')
            var self = this;
            var request = new HttpRequest('/jiuquanzi');
            request.getJSON(function (result) {
                self.songci = result.data.replace(/\n/g, '<br>');
                self.title = result.title;
                $("#show").html(self.songci);
                $("#title").text(self.title);
            });
        },
        ask2: function() {
            var self = this;
            var request = new HttpRequest('/sumuzhe');
            request.getJSON(function (result) {
                self.songci = result.data.replace(/\n/g, '<br>');
                self.title = result.title;
                $("#show").html(self.songci);
                $("#title").text(self.title);
                console.log(self.title)
            });
        },
        ask3: function() {
            var self = this;
            var request = new HttpRequest('/xijiangyue');
            request.getJSON(function (result) {
                console.log(result);
                self.songci = result.data.replace(/\n/g, '<br>');
                self.title = result.title;
                $("#show").html(self.songci);
                $("#title").text(self.title);
            });
        },
        ask4: function() {
            var self = this;
            var request = new HttpRequest('/gancaozi');
            request.getJSON(function (result) {
                console.log(result);
                self.songci = result.data.replace(/\n/g, '<br>');
                self.title = result.title;
                $("#show").html(self.songci);
                $("#title").text(self.title);
            });
        },
        ask5: function() {
            var self = this;
            var request = new HttpRequest('/shengchazi');
            request.getJSON(function (result) {
                console.log(result);
                self.songci = result.data.replace(/\n/g, '<br>');
                self.title = result.title;
                $("#show").html(self.songci);
                $("#title").text(self.title);
            });
        }
    }
});