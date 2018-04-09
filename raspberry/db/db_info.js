module.exports = (function() {
    return {
        local: { // localhost
            host: 'localhost',
            port: '3306',
            user: 'pi',
            password: 'won1228',
            database: 'iof'
        },
        real: { // real server db info
            host: 'localhost',
            port: '3306',
            user: 'pi',
            password: 'won1228',
            database: 'iof'
        },
        dev: { // dev server db info
            host: 'localhost',
            port: '3306',
            user: 'pi',
            password: 'won1228',
            database: 'iof'
        }
    }
})();