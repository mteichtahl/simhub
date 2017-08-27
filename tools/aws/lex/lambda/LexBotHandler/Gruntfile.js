var grunt = require('grunt');
grunt.loadNpmTasks('grunt-aws-lambda');
grunt.loadNpmTasks('grunt-copy');
grunt.loadNpmTasks('grunt-run');
grunt.loadNpmTasks('grunt-aws');

grunt.initConfig({

  // config: grunt.file.readJSON("common/config.json"),

  thisFile: {
    lambdaPackageName: 'LexBotHandler',
    lambdaFunctionName: 'KeyValQuery-LexBotHandler'
  },

  aws: grunt.file.readJSON(
      grunt.option('credentials') ? grunt.option('credentials') :
                                    '/Users/teichtah/.aws/credentials.json'),

  lambda_invoke:
      {default: {options: {file_name: 'index.js', event: 'test_event.json'}}},
  lambda_deploy: {
    dev: {
      arn:
          'arn:aws:lambda:<%= aws.region %>:<%= aws.accountId %>:function:<%= thisFile.lambdaFunctionName %>',
      options: {
        accessKeyId: '<%= aws.accessKeyId %>',
        secretAccessKey: '<%= aws.secretAccessKey %>',
        region: '<%= aws.region %>',

        enableVersioning: true,
        aliases: 'DEV'
      }
    }
  },
  lambda_package: {
    dev: {
      options: {
        accessKeyId: '<%= aws.accessKeyId %>',
        secretAccessKey: '<%= aws.secretAccessKey %>',
        region: '<%= aws.region %>',
        include_time: false,
        include_version: false
      }
    }
  },
  copy: {
    options: {punctuation: ''},
    files: {
      cwd: '../common/',
      expand: true,
      flatten: false,
      src: '*',
      dest: 'common/',
      filter: 'isFile'
    },
  },

  run: {
    options: {
        // Task-specific options go here.
    },

    // Pull in the local dependencies that are not yet published to NPM
    ensure_local_dependencies_up_to_date: {cmd: 'npm', args: ['install']}
  },

  s3: {
    options: {
      accessKeyId: '<%= aws.accessKeyId %>',
      secretAccessKey: '<%= aws.secretAccessKey %>',
      region: '<%= aws.region %>',
      bucket: 'simhub-keyvalquery-<%= aws.region %>',
      gzip: false
    },
    build: {
      cwd: 'dist/',
      src: '<%= thisFile.lambdaPackageName %>_latest.zip',
      dest: 'KeyValQuery/master-artefacts/lambda/'
    }
  },

});

grunt.registerTask(
    'deploy', ['copy', 'lambda_package:dev', 'lambda_deploy:dev'])
grunt.registerTask('package', ['copy', 'lambda_package'])
grunt.registerTask('push', ['copy', 'package', 's3'])
grunt.registerTask(
    'invoke',
    ['copy', 'run:ensure_local_dependencies_up_to_date', 'lambda_invoke'])
grunt.registerTask('default', ['invoke'])
