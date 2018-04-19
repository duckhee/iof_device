module.exports = (function() {
    return {
        local: {
            connectionLimit: '5',
            host: 'localhost',
            port: '3306',
            user: 'candh',
            password: 'candh3869',
            database: 'iof'
        },
        real: {
            host: 'localhost',
            port: '3306',
            user: 'candh',
            password: 'candh3869',
            database: 'iof'
        },
        dev: {
            host: 'localhost',
            port: '3306',
            user: 'candh',
            password: 'candh3869',
            database: 'iof_dev'
        }
    }
})