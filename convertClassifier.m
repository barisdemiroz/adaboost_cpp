function convertClassifier( model, outputFile )
    depth = model.treeDepth;
    depth = 2;
    warning('Using fixed depth=2 due to variable length stumps.');
    
    nWeak = size(model.fids,2);
        
    nNodes = 2^depth - 1;
    
    f = fopen(outputFile, 'w');
    fwrite(f, depth, 'uint32');
    fwrite(f, nWeak, 'uint32');
    fwrite(f, model.fids(1:nNodes,:), 'uint32');
    fwrite(f, model.thrs(1:nNodes,:), 'float64');
    fwrite(f, model.hs(nNodes+1:end,:), 'float64');
    fclose(f);
end

